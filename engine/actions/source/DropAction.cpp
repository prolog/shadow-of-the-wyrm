#include "ActionManager.hpp"
#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DropAction.hpp"
#include "DropScript.hpp"
#include "FeatureDescriber.hpp"
#include "FeatureGenerator.hpp"
#include "GameUtils.hpp"
#include "IFeatureManipulatorFactory.hpp"
#include "ItemFilterFactory.hpp"
#include "ItemIdentifier.hpp"
#include "ItemProperties.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "OptionScreen.hpp"
#include "RaceManager.hpp"
#include "ReligionManager.hpp"
#include "RNG.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "SeedCalculator.hpp"
#include "TextMessages.hpp"
#include "Tile.hpp"
#include "TileGenerator.hpp"
#include "TreeSpeciesFactory.hpp"

using namespace std;

// NPC drop version
ActionCostValue DropAction::drop(CreaturePtr creature, const string& drop_item_id)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION;
  Game& game = Game::instance();

  if (creature != nullptr)
  {
    ItemPtr item_to_drop = creature->get_inventory()->get_from_id(drop_item_id);
    acv = do_drop(creature, game.get_current_map(), item_to_drop, false);
  }

  return acv;
}

// Drop the item on to the square, if possible.
ActionCostValue DropAction::drop(CreaturePtr dropping_creature, ActionManager * const am)
{  
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  
  Game& game = Game::instance();
  
  if (dropping_creature)
  {
    if (game.get_current_map()->get_map_type() == MapType::MAP_TYPE_WORLD)
    {
      handle_world_drop(dropping_creature);
    }
    else
    {
      list<IItemFilterPtr> no_filter = ItemFilterFactory::create_empty_filter();
      vector<ItemPtr> items_to_drop = am->inventory_multiple(dropping_creature, dropping_creature->get_inventory(), no_filter, {}, false, true);
      
      if (items_to_drop.empty())
      {
        handle_no_item_dropped(dropping_creature);
      }
      else // Item selected
      {
        for (ItemPtr i : items_to_drop)
        {
          action_cost_value += do_drop(dropping_creature, game.get_current_map(), i, items_to_drop.size() > 1);
        }
      }      
    }
  }
  
  return action_cost_value;
}

// Handle trying to drop stuff on the world map, which is not a valid case.
void DropAction::handle_world_drop(CreaturePtr creature)
{  
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature->get_is_player());
    string drop_not_allowed = StringTable::get(ActionTextKeys::ACTION_DROP_NOT_ALLOWED);
    
    manager.add_new_message(drop_not_allowed);
    manager.send();
  }  
}

// Handle trying to drop an invalid quantity (0, "a bajillion", etc)
void DropAction::handle_invalid_drop_quantity(CreaturePtr creature)
{  
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, true);
    manager.clear_if_necessary();
    string invalid_drop_quantity = StringTable::get(ActionTextKeys::ACTION_DROP_INVALID_QUANTITY);
    manager.add_new_message(invalid_drop_quantity);
    manager.send();
  }
}

// Show the description of the item being dropped, if applicable
void DropAction::handle_item_dropped_message(CreaturePtr creature, IInventoryPtr inv, ItemPtr item)
{  
  if (item && creature)
  {
    Game& game = Game::instance();
    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, GameUtils::is_creature_in_player_view_map(game, creature->get_id()));

    CurrentCreatureAbilities cca;
    string drop_message = TextMessages::get_item_drop_message(creature, !cca.can_see(creature), item);
    manager.add_new_message(drop_message);

    if (inv)
    {
      string inv_drop_effect_sid = inv->get_drop_effect_sid();

      if (!inv_drop_effect_sid.empty())
      {
        manager.add_new_message(StringTable::get(inv_drop_effect_sid));
      }
    }

    manager.send();
  }
  // If it's not the player, and the player is in range, inform the player
  // what the creature dropped.
  else
  {
    // ...
  }  
}

// Handle the case where the intent was to drop, but then nothing was selected.
void DropAction::handle_no_item_dropped(CreaturePtr creature)
{  
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, true);
    string no_item_to_drop = StringTable::get(ActionTextKeys::ACTION_DROP_NO_ITEM_SELECTED);
    
    manager.add_new_message(no_item_to_drop);
    manager.send();
  }
}

void DropAction::handle_seed_planted_message(CreaturePtr creature, ItemPtr seed)
{
  if (creature != nullptr && seed != nullptr && creature->get_is_player())
  {
    CurrentCreatureAbilities cca;
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, true);
    ItemIdentifier iid;

    string seed_message = ActionTextKeys::get_seed_planted_message(!cca.can_see(creature), iid.get_appropriate_usage_description(seed));

    manager.add_new_message(seed_message);
    manager.send();
  }
}

// Do the actual dropping of items.
ActionCostValue DropAction::do_drop(CreaturePtr creature, MapPtr current_map, ItemPtr item_to_drop, const bool multi_item)
{
  ActionCostValue action_cost_value = ActionCostConstants::NO_ACTION;
  TilePtr creatures_tile = MapUtils::get_tile_for_creature(current_map, creature);

  // Redraw the main screen so that any interaction via scripts looks good.
  Game& game = Game::instance();
  game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
  game.get_display()->redraw();

  if (item_to_drop)
  {
    uint quantity = item_to_drop->get_quantity();
    uint selected_quantity = quantity;
    string grave_tile_type = item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_GRAVE_TILE_TYPE);
    string wall_tile_type = item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_WALL_TILE_TYPE);
    string floor_tile_type = item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_FLOOR_TILE_TYPE);
    string water_tile_type = item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_WATER_TILE_TYPE);
    string feature_ids = item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_BUILD_FEATURE_CLASS_IDS);

    bool building_material = !grave_tile_type.empty() ||
                             !wall_tile_type.empty() || 
                             !floor_tile_type.empty() || 
                             !water_tile_type.empty() || 
                             !feature_ids.empty();

    if (building_material)
    {
      selected_quantity = 1;
    }
    
    if (quantity > 1)
    {
      if (!multi_item)
      {
        selected_quantity = get_drop_quantity(creature, quantity);
      }
    }

    // Drop quantity
    if (!item_to_drop->is_valid_quantity(selected_quantity))
    {
      handle_invalid_drop_quantity(creature);
    }
    else
    {
      bool drop_item = true;
      uint old_item_quantity = item_to_drop->get_quantity() - selected_quantity;
      item_to_drop->set_quantity(old_item_quantity);

      if (build_with_dropped_item(creature, current_map, creatures_tile, building_material, grave_tile_type, wall_tile_type, floor_tile_type, water_tile_type, feature_ids))
      {
        selected_quantity--;

        // If we built, reduce the stack size by 1. If a single item was
        // selected, ensure we don't follow the regular drop logic.
        if (selected_quantity == 0)
        {
          drop_item = false;
        }

        GameUtils::make_map_permanent(game, creature, current_map);
        creatures_tile = MapUtils::get_tile_for_creature(current_map, creature);
      }

      ItemPtr new_item = ItemPtr(item_to_drop->clone_with_new_id());
      new_item->set_quantity(selected_quantity);

      // If the item is a seed or a pit, don't actually set it on the tile,
      // and set the relevant tile and map properties.
      string tree_species_id = item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_TREE_SPECIES_ID);
      string remains = item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_REMAINS);
      string plantable_food = item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_PLANTABLE_FOOD);
      Coordinate creature_coord = MapUtils::get_coordinate_for_creature(current_map, creature);

      if (!remains.empty() && creatures_tile->has_been_dug())
      {
        bury_remains(creature, item_to_drop->get_additional_property(ConsumableConstants::CORPSE_RACE_ID), selected_quantity, creature_coord, creatures_tile, current_map);
      }
      else if (String::to_bool(plantable_food) && creatures_tile->has_been_dug())
      {
        std::map<string, string> food_planting_properties = { {ItemProperties::ITEM_PROPERTIES_ID, item_to_drop->get_base_id()}, 
                                                              {ItemProperties::ITEM_PROPERTIES_PLANTABLE_FOOD_MIN_QUANTITY, item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_PLANTABLE_FOOD_MIN_QUANTITY)}, 
                                                              {ItemProperties::ITEM_PROPERTIES_PLANTABLE_FOOD_MAX_QUANTITY, item_to_drop->get_additional_property(ItemProperties::ITEM_PROPERTIES_PLANTABLE_FOOD_MAX_QUANTITY)} };

        bool planted = plant_food(creature, food_planting_properties, creature_coord, creatures_tile, current_map);

        if (planted)
        {
          handle_seed_planted_message(creature, item_to_drop);
        }
      }
      else if (!tree_species_id.empty() && creatures_tile->has_been_dug())
      {
        bool planted = plant_seed(creature, { {ItemProperties::ITEM_PROPERTIES_TREE_SPECIES_ID, tree_species_id} }, creature_coord, creatures_tile, current_map);

        if (planted)
        {
          handle_seed_planted_message(creature, item_to_drop);
        }
      }
      else
      {
        if (creatures_tile && creature && drop_item)
        {
          Coordinate drop_coord = current_map->get_location(creature->get_id());

          IInventoryPtr inv = creatures_tile->get_items();
          inv->merge_or_add(new_item, InventoryAdditionType::INVENTORY_ADDITION_FRONT);

          // Display a message if appropriate.
          // If it's the player, remind the user what he or she dropped.
          handle_item_dropped_message(creature, inv, new_item);

          // Do any of the creatures watching this have drop scripts?
          handle_reacting_creature_drop_scripts(creature, current_map, new_item, drop_coord);

          // If there's a feature present, invoke the manipulator to see
          // if there are any actions that need to be done.  This really
          // only matters for altars at the moment.
          if (creatures_tile->has_feature())
          {
            FeaturePtr feature = creatures_tile->get_feature();
            FeatureManipulatorPtr feature_manip = IFeatureManipulatorFactory::create_manipulator(feature);

            if (feature_manip != nullptr)
            {
              feature_manip->drop(creature, creatures_tile, new_item);
            }
          }
        }
      }
      
      // Remove it from the inventory, if the quantity is now zero.
      if (item_to_drop->get_quantity() == 0)
      {
        creature->get_inventory()->remove(item_to_drop->get_id());
      }

      // Advance the turn
      action_cost_value = get_action_cost_value(creature);
    }
  }
  
  return action_cost_value;
}

// Get the quantity to drop
uint DropAction::get_drop_quantity(CreaturePtr creature, const uint max_quantity) const
{  
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, true);
    Game& game = Game::instance();
    game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
              
    // Prompt the user in the message buffer
    string quantity_prompt = StringTable::get(ActionTextKeys::ACTION_DROP_QUANTITY_PROMPT);

    manager.add_new_message(quantity_prompt);
    manager.send();
  }
  
  // Get quantity
  return creature->get_decision_strategy()->get_count(max_quantity);
}

bool DropAction::plant_food_or_seed(CreaturePtr creature, const map<string, string>& props, const Coordinate& coords, TilePtr tile, MapPtr current_map, const bool is_food)
{
  bool planted = false;

  if (!props.empty() && creature != nullptr && tile != nullptr && current_map != nullptr)
  {
    Game& game = Game::instance();
    World* world = game.get_current_world();
    tile->set_additional_property(TileProperties::TILE_PROPERTY_PLANTED, to_string(true));

    if (world != nullptr && current_map->get_map_type() == MapType::MAP_TYPE_OVERWORLD)
    {
      planted = is_food ? plant_food(creature, props, coords, tile, current_map) : plant_seed(creature, props, coords, tile, current_map);
    }

    if (!current_map->get_permanent())
    {
      GameUtils::make_map_permanent(game, creature, current_map);
    }

    game.get_deity_action_manager_ref().notify_action(creature, current_map, CreatureActionKeys::ACTION_PLANT_SEEDS, true);
    planted = true;
  }

  return planted;
}

bool DropAction::plant_food(CreaturePtr creature, const map<string, string>& props, const Coordinate& coords, TilePtr tile, MapPtr current_map)
{
  bool planted = false;

  if (creature != nullptr && tile != nullptr && current_map != nullptr)
  {
    auto item_id_it = props.find(ItemProperties::ITEM_PROPERTIES_ID);
    auto min_q_it = props.find(ItemProperties::ITEM_PROPERTIES_PLANTABLE_FOOD_MIN_QUANTITY);
    auto max_q_it = props.find(ItemProperties::ITEM_PROPERTIES_PLANTABLE_FOOD_MAX_QUANTITY);

    if (item_id_it != props.end() && min_q_it != props.end() && max_q_it != props.end())
    {
      string item_id = item_id_it->second;
      string min_q = min_q_it->second;
      string max_q = max_q_it->second;

      // ...

      planted = true;
    }
  }

  return planted;
}

// Plant a seed for a particular type of tree.
bool DropAction::plant_seed(CreaturePtr creature, const map<string, string>& props, const Coordinate& coords, TilePtr tile, MapPtr current_map)
{
  bool planted = false;

  if (creature != nullptr && tile != nullptr && current_map != nullptr)
  {
    Game& game = Game::instance();
    World* world = game.get_current_world();
    TreeSpeciesFactory tsf;

    auto t_it = props.find(ItemProperties::ITEM_PROPERTIES_TREE_SPECIES_ID);

    if (t_it != props.end())
    {
      string tree_species_id = t_it->second;
      TreeSpecies ts = tsf.create_tree_species(static_cast<TreeSpeciesID>(String::to_int(tree_species_id)));
      TileTransform tt(coords, ts.get_tile_type(), TileType::TILE_TYPE_UNDEFINED, { { ItemProperties::ITEM_PROPERTIES_TREE_SPECIES_ID, tree_species_id } });

      SeedCalculator sc;
      Date current_date = world->get_calendar().get_date();
      double sprout_time = sc.calculate_sprouting_seconds(current_date);
      vector<TileTransform>& tt_v = current_map->get_tile_transforms_ref()[sprout_time];

      tt_v.push_back(tt);
    }
  }
  
  return planted;
}

// Bury the remains of something once living
bool DropAction::bury_remains(CreaturePtr creature, const string& remains_race_id, const uint selected_quantity, const Coordinate& coords, TilePtr tile, MapPtr current_map)
{
  bool buried = false;

  if (creature != nullptr)
  {
    // Mark the tile as containing remains and then do the deity notification.
    tile->set_additional_property(TileProperties::TILE_PROPERTY_REMAINS, std::to_string(true));

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, GameUtils::is_creature_in_player_view_map(Game::instance(), creature->get_id()));
    manager.add_new_message(TextMessages::get_burial_message(creature));
    manager.send();

    ReligionManager rm;
    Deity* deity = rm.get_active_deity(creature);

    if (deity != nullptr)
    {
      RaceManager racem;
      vector<string> bury_race_ids = deity->get_burial_races();

      for (const string& cur_race : bury_race_ids)
      {
        if (racem.is_race_or_descendent(remains_race_id, cur_race))
        {
          Game::instance().get_deity_action_manager_ref().notify_action(creature, current_map, CreatureActionKeys::ACTION_BURY_REMAINS, true, selected_quantity);

          buried = true;
          break;
        }
      }
    }
  }

  return buried;
}

void DropAction::handle_reacting_creature_drop_scripts(CreaturePtr creature, MapPtr current_map, ItemPtr new_item, const Coordinate& drop_coord)
{
  Game& game = Game::instance();

  // For all the creatures that can see the dropping creature, run
  // any associated drop scripts.
  map<string, CreaturePtr> creatures = current_map->get_creatures();
  for (const auto& cr_pair : creatures)
  {
    CreaturePtr reacting_creature = cr_pair.second;

    if (reacting_creature != nullptr)
    {
      MapPtr fov_map = cr_pair.second->get_decision_strategy()->get_fov_map();

      if (fov_map)
      {
        map<string, CreaturePtr> fov_creatures = fov_map->get_creatures();
        if (fov_creatures.find(creature->get_id()) != fov_creatures.end())
        {
          ScriptDetails sd = reacting_creature->get_event_script(CreatureEventScripts::CREATURE_EVENT_SCRIPT_DROP);

          if (RNG::percent_chance(sd.get_chance()))
          {
            DropScript ds;
            ds.execute(game.get_script_engine_ref(), sd.get_script(), creature->get_id(), reacting_creature, new_item, drop_coord);
          }
        }
      }
    }
  }
}

bool DropAction::build_with_dropped_item(CreaturePtr creature, MapPtr map, TilePtr tile, const bool building_material, const string& grave_tile_type_s, const string& wall_tile_type_s, const string& floor_tile_type_s, const string& water_tile_type_s, const string& feature_ids)
{
  bool built = false;

  if (!building_material || !tile || !map || !creature || !creature->get_is_player())
  {
    return false;
  }

  CurrentCreatureAbilities cca;
  if (!cca.can_see(creature))
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_BUILD_BLIND));
    manager.send();

    return false;
  }

  // Can we build a grave?
  if (tile->has_remains())
  {
    TileType grave_tile_type = static_cast<TileType>(String::to_int(grave_tile_type_s));
    built = build_grave_with_dropped_item(creature, map, tile, grave_tile_type);
  }

  // Can we build flooring/road?
  if (!built && tile->has_been_dug() && !floor_tile_type_s.empty())
  {
    TileType floor_tile_type = static_cast<TileType>(String::to_int(floor_tile_type_s));
    built = build_floor_with_dropped_item(creature, map, tile, floor_tile_type);
  }

  // Can we build a wall?
  if (!built && !wall_tile_type_s.empty())
  {
    TileType wall_tile_type = static_cast<TileType>(String::to_int(wall_tile_type_s));
    built = build_wall_with_dropped_item(creature, map, tile, wall_tile_type, false);
  }

  // Can we build on adjacent water tiles?
  if (!built && !water_tile_type_s.empty())
  {
    TileDirectionMap tdm = MapUtils::get_adjacent_tiles_to_creature(map, creature);
    bool water_nearby = false;

    for (auto tdm_pair : tdm)
    {
      if (tdm_pair.second && tdm_pair.second->get_tile_base_super_type() == TileSuperType::TILE_SUPER_TYPE_WATER)
      {
        water_nearby = true;
      }
    }

    if (water_nearby)
    {
      TileType water_tile_type = static_cast<TileType>(String::to_int(water_tile_type_s));
      built = build_wall_with_dropped_item(creature, map, tile, water_tile_type, true);
    }
  }

  // Can we build a feature?
  if (!built && !feature_ids.empty())
  {
    vector<string> feature_s_ids = String::create_string_vector_from_csv_string(feature_ids);
    built = build_feature_with_dropped_item(creature, map, tile, feature_s_ids);
  }

  return built;
}

bool DropAction::build_wall_with_dropped_item(CreaturePtr creature, MapPtr map, TilePtr tile, const TileType wall_tile_type, const bool allow_build_on_water)
{
  bool built = false;
  IMessageManager& manager = MM::instance();
  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_PROMPT_BUILD_WALL));
  manager.send();

  CommandFactoryPtr command_factory = std::make_unique<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_unique<KeyboardCommandMap>();
  CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), 0, false);
  string build_msg_sid;

  if (base_command != nullptr)
  {
    DirectionalCommand* dcommand;
    dcommand = dynamic_cast<DirectionalCommand*>(base_command.get());

    if (dcommand)
    {
      Direction d = dcommand->get_direction();
      Coordinate pl_coord = map->get_location(creature->get_id());
      Coordinate build_coord = CoordUtils::get_new_coordinate(pl_coord, d);
      TilePtr build_tile = map->at(build_coord);

      if (build_tile == nullptr)
      {
        build_msg_sid = ActionTextKeys::ACTION_BUILD_WALL_NO_TILE;
      }
      else
      {
        TileSuperType tst = build_tile->get_tile_base_super_type();

        if (build_tile->get_movement_multiplier() == 0)
        {
          build_msg_sid = ActionTextKeys::ACTION_BUILD_WALL_PRESENT;
        }
        else if (build_tile->has_creature())
        {
          build_msg_sid = ActionTextKeys::ACTION_BUILD_WALL_CREATURE_PRESENT;
        }
        else if (build_tile->has_feature())
        {
          build_msg_sid = ActionTextKeys::ACTION_BUILD_WALL_FEATURE_PRESENT;
        }
        else if (tst == TileSuperType::TILE_SUPER_TYPE_AIR)
        {
          build_msg_sid = ActionTextKeys::ACTION_BUILD_WALL_AIR;
        }
        else if (tst == TileSuperType::TILE_SUPER_TYPE_WATER && !allow_build_on_water)
        {
          build_msg_sid = ActionTextKeys::ACTION_BUILD_WALL_WATER;
        }
        else if ((tst == TileSuperType::TILE_SUPER_TYPE_GROUND && !allow_build_on_water) ||
          (tst == TileSuperType::TILE_SUPER_TYPE_WATER && allow_build_on_water))
        {
          IInventoryPtr build_tile_items = build_tile->get_items();
          if (build_tile_items->has_items())
          {
            manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_BUILD_WALL_DISPLACE_ITEMS));
            manager.send();

            vector<Coordinate> adj_coords = CoordUtils::get_adjacent_map_coordinates(map->size(), build_coord.first, build_coord.second);
            std::shuffle(adj_coords.begin(), adj_coords.end(), RNG::get_engine());

            for (const auto& ac : adj_coords)
            {
              TilePtr adj_tile = map->at(ac);

              if (adj_tile && adj_tile->get_items()->get_allows_items() == AllowsItemsType::ALLOWS_ITEMS)
              {
                IInventoryPtr adj_items = adj_tile->get_items();
                build_tile_items->transfer_to(adj_items);
              }
            }
          }

          TileGenerator tg;
          TilePtr new_tile = tg.generate(wall_tile_type);
          new_tile->transform_from(build_tile);
          map->insert(build_coord, new_tile);

          build_msg_sid = ActionTextKeys::ACTION_BUILD_WALL;
          built = true;
        }
      }

      if (!build_msg_sid.empty())
      {
        manager.add_new_message(StringTable::get(build_msg_sid));
        manager.send();
      }
    }
  }

  return built;
}

bool DropAction::build_grave_with_dropped_item(CreaturePtr creature, MapPtr map, TilePtr tile, const TileType grave_tile_type)
{
  if (creature == nullptr || map == nullptr || tile == nullptr)
  {
    return false;
  }

  // Check to see if building is intended.
  bool built = false;

  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  manager.add_new_confirmation_message(TextMessages::get_confirmation_message(ActionTextKeys::ACTION_PROMPT_BUILD_GRAVE));
  bool confirmation = creature->get_decision_strategy()->get_confirmation();

  if (confirmation)
  {
    TileGenerator tg;
    TilePtr new_tile = tg.generate(grave_tile_type);
    Coordinate c = map->get_location(creature->get_id());
    new_tile->transform_from(tile);
    map->insert(c, new_tile);

    new_tile->remove_additional_property(TileProperties::TILE_PROPERTY_REMAINS);
    new_tile->set_additional_property(TileProperties::TILE_PROPERTY_PCT_CHANCE_ITEMS, to_string(0));
    new_tile->set_additional_property(TileProperties::TILE_PROPERTY_PCT_CHANCE_UNDEAD, to_string(0));

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_BUILD_GRAVE));
    manager.send();

    built = true;
  }

  return built;
}

bool DropAction::build_floor_with_dropped_item(CreaturePtr creature, MapPtr map, TilePtr tile, const TileType floor_tile_type)
{
  // Check to see if building is intended.
  bool built = false;

  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  vector<TileType> tile_types = { floor_tile_type, TileType::TILE_TYPE_ROAD };
  TileGenerator tg;
  vector<string> descs;

  for (size_t i = 0 ; i < tile_types.size(); i++)
  {
    const TileType tt = tile_types.at(i);
    TilePtr new_tile = tg.generate(tt);

    if (new_tile != nullptr)
    {
      descs.push_back(std::to_string(i) + "=" + StringTable::get(new_tile->get_tile_description_sid()));
    }
  }

  size_t idx = get_build_option(descs);

  if (idx < tile_types.size())
  {
    TileType tt = tile_types.at(idx);
    TilePtr new_tile = tg.generate(tt);
    Coordinate c = map->get_location(creature->get_id());
    new_tile->transform_from(tile);
    map->insert(c, new_tile);

    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_BUILD_FLOOR));
    manager.send();

    built = true;
  }

  return built;
}

bool DropAction::build_feature_with_dropped_item(CreaturePtr creature, MapPtr map, TilePtr tile, const vector<string>& feature_ids)
{
  bool built = false;

  if (creature == nullptr || map == nullptr || tile == nullptr || tile->has_feature() || feature_ids.empty())
  {
    return false;
  }

  vector<ClassIdentifier> class_ids;
  vector<string> descs;

  for (size_t i = 0; i < feature_ids.size(); i++)
  {
    string s = feature_ids.at(i);
    ClassIdentifier cl_id = static_cast<ClassIdentifier>(String::to_int(s));
    FeaturePtr feature = FeatureGenerator::create_feature(cl_id);

    if (feature != nullptr)
    {
      FeatureDescriber fd(feature);

      descs.push_back(std::to_string(i) + "=" + fd.describe(false));
      class_ids.push_back(cl_id);
    }
  }

  ClassIdentifier cl_id = ClassIdentifier::CLASS_ID_NULL;

  if (class_ids.size() == 1)
  {
    cl_id = class_ids.at(0);
  }
  else
  {
    size_t idx = get_build_option(descs);

    if (idx < class_ids.size())
    {
      cl_id = class_ids.at(idx);
    }
  }

  if (cl_id != ClassIdentifier::CLASS_ID_NULL)
  {
    FeaturePtr feature = FeatureGenerator::create_feature(cl_id);

    if (feature != nullptr)
    {
      tile->set_feature(feature);

      FeatureDescriber fd(feature);
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
      manager.add_new_message(TextMessages::get_build_message(fd.describe(false)));
      manager.send();

      built = true;
    }
  }

  return built;
}

size_t DropAction::get_build_option(const vector<string>& options) const
{
  OptionScreen os(Game::instance().get_display(), ScreenTitleTextKeys::SCREEN_TITLE_BUILD, {}, options);
  string option_s = os.display();
  
  return static_cast<size_t>(option_s[0] - 'a');
}

// Dropping always has a base action cost of 1.
ActionCostValue DropAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
