#include "ActionTextKeys.hpp"
#include "Amulet.hpp"
#include "AttackNPCMagicDecision.hpp"
#include "CoordUtils.hpp"
#include "Commands.hpp"
#include "CommandCustomValues.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureProperties.hpp"
#include "CreatureTileSafetyChecker.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DecisionScript.hpp"
#include "DecisionStrategyProperties.hpp"
#include "EngineConversion.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "IMessageManager.hpp"
#include "Log.hpp"
#include "MagicalAbilityChecker.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "NPCDecisionStrategy.hpp"
#include "NPCMagicDecisionFactory.hpp"
#include "RangedCombatApplicabilityChecker.hpp"
#include "RangedCombatUtils.hpp"
#include "RaceManager.hpp"
#include "Ring.hpp"
#include "RNG.hpp"
#include "SearchStrategyFactory.hpp"
#include "Spellbook.hpp"
#include "SpellShapeFactory.hpp"
#include "ThreatConstants.hpp"
#include "Wand.hpp"
#include "WeaponManager.hpp"

using namespace std;

const int NPCDecisionStrategy::PERCENT_CHANCE_USE_ITEM = 40;
const int NPCDecisionStrategy::PERCENT_CHANCE_PICK_UP_USEFUL_ITEM = 75;
const int NPCDecisionStrategy::PERCENT_CHANCE_ADVANCE_TOWARDS_TARGET = 85;
const int NPCDecisionStrategy::PERCENT_CHANCE_CONSIDER_USING_MAGIC = 75;
const int NPCDecisionStrategy::PERCENT_CHANCE_CONSIDER_RANGED_COMBAT = 80;
const int NPCDecisionStrategy::PERCENT_CHANCE_BREED = 15;

NPCDecisionStrategy::NPCDecisionStrategy(ControllerPtr new_controller)
: DecisionStrategy(new_controller)
{
}

// By default, always get/pick up/etc the maximum.
uint NPCDecisionStrategy::get_count(const uint max_count)
{
  return max_count;
}

bool NPCDecisionStrategy::get_confirmation(const bool confirmation_default_value, const bool require_proper_selection)
{
  return true;
}

void NPCDecisionStrategy::set_fov_map(MapPtr new_fov_map)
{
  current_fov_map = new_fov_map;
  update_threats_if_shopkeeper(current_fov_map);
}

void NPCDecisionStrategy::update_threats_if_shopkeeper(MapPtr current_fov_map)
{
  if (current_fov_map != nullptr && String::to_bool(get_property(DecisionStrategyProperties::DECISION_STRATEGY_SHOPKEEPER)))
  {
    CreatureMap potential_thieves = current_fov_map->get_creatures();

    for (const auto& pt_pair : potential_thieves)
    {
      CreaturePtr creature = pt_pair.second;

      if (creature != nullptr && creature->has_unpaid_items() && !threat_ratings.has_threat(creature->get_id()).first)
      {
        MapPtr current_map = Game::instance().get_current_map();
        Coordinate creature_coord = current_map->get_location(creature->get_id());

        // If the creature has unpaid items and is standard outside of a shop
        // perimeter, become hostile.
        if (!MapUtils::is_in_shop_or_adjacent(current_map, creature_coord).first)
        {
          threat_ratings.add_threat(creature->get_id(), ThreatConstants::INITIAL_THREAT_RATING);

          IMessageManager& manager = MM::instance();
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ENRAGED_SHOPKEEPER));
          manager.send();
        }
      }
    }
  }
}

// The basic decision structure for NPCs.  The individual get_decision_for functions are pure virtual within this class,
// and implemented by concrete decision strategies.
CommandPtr NPCDecisionStrategy::get_nonmap_decision(const bool reprompt_on_cmd_not_found, const string& this_creature_id, CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands, int* key_p, const bool refresh_window)
{
  MapPtr nullmap;
  return get_decision(reprompt_on_cmd_not_found, this_creature_id, command_factory, keyboard_commands, nullmap, key_p);
}

CommandPtr NPCDecisionStrategy::get_decision(const bool reprompt_on_cmd_not_found, const string& this_creature_id, CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands, MapPtr view_map, int* key_p)
{
  CommandPtr command;
  
  CommandFactoryType factory_type = command_factory->get_factory_type();
  
  switch(factory_type)
  {
    case CommandFactoryType::COMMAND_FACTORY_TYPE_MAP:
      command = get_decision_for_map(this_creature_id, command_factory, keyboard_commands, view_map);
      break;
    case CommandFactoryType::COMMAND_FACTORY_TYPE_INVENTORY:
      command = get_decision_for_inventory(command_factory, keyboard_commands);
      break;
    case CommandFactoryType::COMMAND_FACTORY_TYPE_EQUIPMENT:
      command = get_decision_for_equipment(command_factory, keyboard_commands);
      break;
    case CommandFactoryType::COMMAND_FACTORY_TYPE_SELECT_TILE:
      command = get_decision_for_tile_selection(command_factory, keyboard_commands);
      break;
    default:
      break;
  }

  return command;
}

CommandPtr NPCDecisionStrategy::get_decision_for_map(const std::string& this_creature_id, CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands, MapPtr view_map)
{
  CommandPtr command;
  
  if (view_map)
  {
    update_threats_to_leader(this_creature_id, view_map);

    if (has_movement_orders() == false)
    {
      command = get_use_item_decision(this_creature_id, view_map);
    }

    if (has_movement_orders() == false)
    {
      if (command == nullptr)
      {
        // Is there something useful to pick up? Humanoids will pick up wands
        // if they know what they do, if the wands cause damage
        command = get_pick_up_decision(this_creature_id, view_map);
      }
    }

    // If the creature has any spells, consider casting a spell, based on
    // low health, nearby hostile creatures, etc.
    if (has_movement_orders() == false)
    {
      if (command == nullptr)
      {
        command = get_magic_decision(this_creature_id, view_map);
      }
    }

    // Breed, potentially.
    // Movement orders can't override this.
    if (command == nullptr)
    {
      command = get_breed_decision(this_creature_id, view_map);
    }

    if (has_movement_orders() == false)
    {
      // Attack if threatened.
      if (command == nullptr)
      {
        command = get_ranged_attack_decision(this_creature_id, view_map);
      }
    }

    if (has_movement_orders() == false)
    {
      if (command == nullptr)
      {
        command = get_attack_decision(this_creature_id, view_map);
      }
    }

    if (has_movement_orders() == false)
    {
      // If not threatened, try a custom (script-based) decision.
      if (command == nullptr)
      {
        command = get_custom_decision(this_creature_id, view_map);
      }
    }
    
    // If no custom decisions fired, attempt movement.
    if (command == nullptr && can_move())
    {
      command = get_movement_decision(this_creature_id, view_map);
    }    
  }

  // If we can't move, or there are no adjacent coordinates to which the NPC can move,
  // the command will be a search command - that can always be done, and will always
  // advance to the next turn.
  if (!command)
  {
    command = std::make_unique<SearchCommand>(-1);
  }
  
  return command;
}

// Decide whether or not to cast a spell.
CommandPtr NPCDecisionStrategy::get_magic_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr magic_command;
  INPCMagicDecisionPtr npc_magic_decision;
  bool suppress_magic = String::to_bool(get_property(DecisionStrategyProperties::DECISION_STRATEGY_SUPPRESS_MAGIC));

  if (view_map != nullptr && !suppress_magic)
  {
    CreaturePtr creature = view_map->get_creature(this_creature_id);
    CurrentCreatureAbilities cca;
    Game& game = Game::instance();
    const SpellMap& spell_map = game.get_spells_ref();
    const set<string> creature_threats = threat_ratings.get_true_threats_without_level();
    std::vector<std::pair<std::string, Direction>> potential_spells;
    MagicalAbilityChecker mac;

    if (creature != nullptr && cca.can_speak(creature))
    {
      SpellKnowledge& sk = creature->get_spell_knowledge_ref();

      if (sk.get_knows_spells() && RNG::percent_chance(PERCENT_CHANCE_CONSIDER_USING_MAGIC))
      {
        SpellKnowledgeMap skm = sk.get_spell_knowledge_map();

        for (const auto& skm_pair : skm)
        {
          const auto& s_it = spell_map.find(skm_pair.first);

          if (skm_pair.second.get_castings() > 0)
          {
            if (s_it == spell_map.end())
            {
              Log::instance().error("Spell ID " + skm_pair.first + " not found for creature base ID " + creature->get_original_id());
              continue;
            }
            else
            {
              const Spell& spell = s_it->second;

              // Only consider the spell if the creature actually has enough
              // AP to cast it!
              if (mac.has_sufficient_power(creature, spell))
              {
                npc_magic_decision = NPCMagicDecisionFactory::create_npc_magic_decision(spell.get_magic_classification());

                if (npc_magic_decision != nullptr)
                {
                  pair<bool, Direction> decision_details = npc_magic_decision->decide(creature, view_map, spell, creature_threats);

                  if (npc_magic_decision && decision_details.first)
                  {
                    potential_spells.push_back(make_pair(spell.get_spell_id(), decision_details.second));
                  }
                }
              }
            }
          }
        }
      }
    }

    if (potential_spells.size() > 0)
    {
      std::shuffle(potential_spells.begin(), potential_spells.end(), RNG::get_engine());
      pair<string, Direction> spell_to_cast = potential_spells.at(0);

      // Create the spell command, adding properties to set the spell details.
      magic_command = make_unique<CastSpellCommand>(-1);
      magic_command->set_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_SELECTED_SPELL_ID, spell_to_cast.first);
      magic_command->set_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_DIRECTION, to_string(static_cast<int>(spell_to_cast.second)));
    }
  }

  return magic_command;
}

// Get the decision for what to attack.
CommandPtr NPCDecisionStrategy::get_attack_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr no_attack;

  // Iterate through the threats in order of threatiness
  ThreatMap threat_map = threat_ratings.get_all_threats();
  ThreatMap::const_reverse_iterator t_it = threat_map.rbegin();
  
  if (view_map != nullptr)
  {
    Coordinate c_this = view_map->get_location(this_creature_id);
    TilePtr this_tile = view_map->at(c_this);

    if (this_tile != nullptr)
    {
      CreaturePtr this_cr = this_tile->get_creature();

      // Ensure that we only attack legitimate threats.
      // Creatures may dislike other creatures, but that won't cause them to attack.
      while (t_it != threat_map.rend() && t_it->first > ThreatConstants::DISLIKE_THREAT_RATING)
      {
        set<string> creature_ids = t_it->second;
        vector<pair<string, int>> threat_distances = get_creatures_by_distance(this_cr, view_map, creature_ids);

        for (const auto& td_pair : threat_distances)
        {
          string threatening_creature_id = td_pair.first;

          // Check the view map to see if the creature exists
          if (view_map->has_creature(threatening_creature_id))
          {
            // Check if adjacent to this_creature_id
            Coordinate c_threat = view_map->get_location(threatening_creature_id);

            if (CoordUtils::are_coordinates_adjacent(c_this, c_threat))
            {
              Direction direction = CoordUtils::get_direction(c_this, c_threat);

              // create movement command, return.
              CommandPtr command = std::make_unique<AttackCommand>(direction, -1);
              return command;
            }
            else
            {
              // If the creature is hostile, and the target is generally far away,
              // advance towards the target, but only do so with a certain
              // probability, to allow for other actions (script decisions, etc).
              if (can_move() && RNG::percent_chance(PERCENT_CHANCE_ADVANCE_TOWARDS_TARGET) && this_cr != nullptr)
              {
                SearchStrategyPtr ss = SearchStrategyFactory::create_search_strategy(SearchType::SEARCH_TYPE_UNIFORM_COST, this_cr); // JCD FIXME WAS BFS...
                Direction direction = CoordUtils::get_direction(c_this, ss->search(view_map, c_this, c_threat));

                if (direction != Direction::DIRECTION_NULL)
                {
                  CommandPtr command = std::make_unique<MovementCommand>(direction, -1);
                  return command;
                }
              }
            }
          }
        }

        // Try the next threat level.
        t_it++;
      }
    }
  }
  
  return no_attack;
}

// If the creature is a breeder, consider whether or not to breed.
CommandPtr NPCDecisionStrategy::get_breed_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr no_breed;
  bool breeds = String::to_bool(get_property(DecisionStrategyProperties::DECISION_STRATEGY_BREEDS));

  if (breeds && RNG::percent_chance(PERCENT_CHANCE_BREED))
  {
    // Only breed if there's at least one threatening creature in the
    // creature's view map.
    set<string> all_threats = threat_ratings.get_true_threats_without_level();
    bool threat_nearby = false;

    for (const string& threat_id : all_threats)
    {
      if (view_map->has_creature(threat_id))
      {
        threat_nearby = true;
        break;
      }
    }

    if (!threat_nearby)
    {
      return no_breed;
    }

    TileDirectionMap tdm = MapUtils::get_adjacent_tiles_to_creature(view_map, view_map->get_creature(this_creature_id));

    for (const auto& tdm_pair : tdm)
    {
      TilePtr tile = tdm_pair.second;

      if (tile != nullptr && tile->has_creature() == false)
      {
        CommandPtr breed = std::make_unique<BreedCommand>(-1);
        return breed;
      }
    }
  }

  return no_breed;
}

// Potentially do a ranged attack
CommandPtr NPCDecisionStrategy::get_ranged_attack_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr no_attack;

  ThreatMap threat_map = threat_ratings.get_all_threats();
  ThreatMap::const_reverse_iterator t_it = threat_map.rbegin();

  if (view_map != nullptr)
  {
    Coordinate c_this = view_map->get_location(this_creature_id);
    TilePtr this_tile = view_map->at(c_this);

    if (this_tile != nullptr)
    {
      CreaturePtr this_cr = this_tile->get_creature();

      RangedCombatApplicabilityChecker rcac;
      if (rcac.can_creature_do_ranged_combat(this_cr).first && RNG::percent_chance(PERCENT_CHANCE_CONSIDER_RANGED_COMBAT))
      {
        while (t_it != threat_map.rend() && t_it->first > ThreatConstants::DISLIKE_THREAT_RATING)
        {
          set<string> creature_ids = t_it->second;
          vector<pair<string, int>> threat_distances = get_creatures_by_distance(this_cr, view_map, creature_ids);

          for (const auto& td_pair : threat_distances)
          {
            string threatening_creature_id = td_pair.first;
            Coordinate threat_c = view_map->get_location(threatening_creature_id);

            if (RangedCombatUtils::is_coord_in_range(threat_c, view_map) && RangedCombatUtils::is_coordinate_obstacle_free(this_cr, c_this, threat_c, view_map))
            {
              TargetMap& tm = this_cr->get_target_map_ref();
              tm[to_string(static_cast<int>(AttackType::ATTACK_TYPE_RANGED))] = make_pair(threatening_creature_id, threat_c);
              CommandPtr command = std::make_unique<FireMissileCommand>(-1);
              command->set_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_SKIP_TARGETTING, Bool::to_string(true));

              return command;
            }
          }

          // Try the next threat level.
          t_it++;
        }
      }
    }
  }

  return no_attack;
}

// Get a custom decision (script-based)
CommandPtr NPCDecisionStrategy::get_custom_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr command;

  if (view_map != nullptr)
  {
    CreaturePtr creature = view_map->get_creature(this_creature_id);

    if (creature != nullptr)
    {
      ScriptDetails decision_script_details = creature->get_event_script(CreatureEventScripts::CREATURE_EVENT_SCRIPT_DECISION);
      string decision_script = decision_script_details.get_script();

      if (!decision_script.empty() && RNG::percent_chance(decision_script_details.get_chance()))
      {
        Game& game = Game::instance();
        ScriptEngine& se = game.get_script_engine_ref();
        DecisionScript ds;

        ActionCostValue acv = ds.execute(se, decision_script, creature);
        if (acv > 0)
        {
          command = std::make_unique<CustomScriptCommand>();
          command->set_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_ACTION_COST_VALUE, std::to_string(acv));
        }
      }
    }
  }

  return command;
}

// Get the decision for where to move.
// Move stupidly (randomly) when no threat is present.
CommandPtr NPCDecisionStrategy::get_movement_decision(const string& this_creature_id, MapPtr view_map)
{   
  CommandPtr movement_command;

  Game& game = Game::instance();
  
  MapPtr current_map = game.get_current_map();

  if (current_map != nullptr)
  {
    Coordinate this_creature_coords = current_map->get_location(this_creature_id);
    TilePtr this_creature_tile = current_map->at(this_creature_coords);
    CreaturePtr this_creature = this_creature_tile->get_creature();

    // Is the creature a sentinel?  Sentinels are just NPCs that stay in one
    // place, moving only to pursue when attacked.
    bool sentinel = String::to_bool(get_property(DecisionStrategyProperties::DECISION_STRATEGY_SENTINEL));
    bool ordered_sentinel = String::to_bool(get_property(DecisionStrategyProperties::DECISION_STRATEGY_ORDERED_SENTINEL));
    if ((sentinel || ordered_sentinel) &&
         this_creature &&
         MapUtils::hostile_creature_exists(this_creature_id, view_map) == false)
    {
      return movement_command;
    }

    string follow_id = get_property(DecisionStrategyProperties::DECISION_STRATEGY_FOLLOW_CREATURE_ID);
    if (!follow_id.empty())
    {
      movement_command = get_follow_direction(view_map, this_creature, this_creature_coords, follow_id);

      if (movement_command != nullptr)
      {
        return movement_command;
      }
    }

    string search_pct = get_property(DecisionStrategyProperties::DECISION_STRATEGY_SEARCH_PCT);

    if (!search_pct.empty())
    {
      if (RNG::percent_chance(String::to_int(search_pct)))
      {
        movement_command = std::make_unique<SearchCommand>(-1);
        return movement_command;
      }
    }

    // If the creature has automove coordinates, favour those.
    Coordinate am_c = get_automove_coords();

    if (am_c != CoordUtils::end())
    {
      Coordinate c_this = view_map->get_location(this_creature_id);
      TilePtr this_tile = view_map->at(c_this);

      if (this_tile != nullptr)
      {
        CreaturePtr this_cr = this_tile->get_creature();

        SearchStrategyPtr ss = SearchStrategyFactory::create_search_strategy(SearchType::SEARCH_TYPE_ASTAR, this_cr);
        Direction direction = CoordUtils::get_direction(c_this, ss->search(view_map, c_this, am_c));

        if (direction != Direction::DIRECTION_NULL)
        {
          CommandPtr command = std::make_unique<MovementCommand>(direction, -1);
          return command;
        }
      }
    }

    Dimensions current_dimensions = current_map->size();

    int this_row = this_creature_coords.first;
    int this_col = this_creature_coords.second;

    vector<Coordinate> adjacent_coordinates = CoordUtils::get_adjacent_map_coordinates(current_dimensions, this_row, this_col);
    vector<Coordinate> choice_coordinates = get_adjacent_safe_coordinates_without_creatures(current_map, adjacent_coordinates, this_creature);

    // If the creature is a shopkeeper, prefer movement on to shop tiles when
    // in a shop.
    bool shopkeeper = String::to_bool(get_property(DecisionStrategyProperties::DECISION_STRATEGY_SHOPKEEPER));
    if (shopkeeper && MapUtils::is_in_shop_or_adjacent(current_map, current_map->get_location(this_creature_id)).first)
    {
      std::shuffle(choice_coordinates.begin(), choice_coordinates.end(), RNG::get_engine());

      for (const Coordinate& cc : choice_coordinates)
      {
        if (MapUtils::is_in_shop_or_adjacent(current_map, cc).first)
        {
          movement_command = std::make_unique<MovementCommand>(CoordUtils::get_direction(this_creature_coords, cc), -1);
          break;
        }
      }
    }
    else
    {
      // Pick a random empty coordinate.
      if (!choice_coordinates.empty())
      {
        Coordinate movement_coord = choice_coordinates.at(RNG::range(0, choice_coordinates.size() - 1));
        Direction direction = CoordUtils::get_direction(this_creature_coords, movement_coord);
        movement_command = std::make_unique<MovementCommand>(direction, -1);
      }
    }
  }

  return movement_command;
}

CommandPtr NPCDecisionStrategy::get_pick_up_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr pu_cmd;
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (map != nullptr && RNG::percent_chance(PERCENT_CHANCE_PICK_UP_USEFUL_ITEM))
  {
    CreaturePtr creature = map->get_creature(this_creature_id);
    RaceManager rm;
    Race* race = rm.get_race(creature->get_race_id());

    if (creature != nullptr && race != nullptr && race->get_has_pockets())
    {
      BurdenLevel bl = BurdenLevelConverter::to_burden_level(creature);
      TilePtr tile = MapUtils::get_tile_for_creature(map, creature);

      // Creatures won't pick up if they're already burdened.
      if (tile != nullptr && bl == BurdenLevel::BURDEN_LEVEL_UNBURDENED)
      {
        IInventoryPtr inv = tile->get_items();

        if (inv != nullptr)
        {
          list<ItemPtr>& items = inv->get_items_ref();

          for (ItemPtr item : items)
          {
            // NPCs don't pick up shop items, this is too hazardous to their
            // health!
            if (item != nullptr && !item->get_unpaid())
            {
              ItemType itype = item->get_type();

              if (itype == ItemType::ITEM_TYPE_WEAPON)
              {
                pu_cmd = get_pick_up_weapon_decision(creature, item);
              }
              else if (itype == ItemType::ITEM_TYPE_AMULET)
              {
                pu_cmd = get_pick_up_amulet_decision(creature, item);
              }
              else if (itype == ItemType::ITEM_TYPE_RING)
              {
                pu_cmd = get_pick_up_ring_decision(creature, item);
              }
              else if (itype == ItemType::ITEM_TYPE_AMMUNITION)
              {
                pu_cmd = get_pick_up_ammunition_decision(creature, item);
              }
              else if (itype == ItemType::ITEM_TYPE_WAND)
              {
                pu_cmd = get_pick_up_wand_decision(creature, item);
              }
              else if (itype == ItemType::ITEM_TYPE_SPELLBOOK)
              {
                pu_cmd = get_pick_up_book_decision(creature, item);
              }

              if (pu_cmd != nullptr)
              {
                return pu_cmd;
              }
            }
          }
        }
      }
    }
  }

  return pu_cmd;
}

CommandPtr NPCDecisionStrategy::get_use_item_decision(const string& this_creature_id, MapPtr view_map)
{
  CommandPtr use_cmd;
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  if (map != nullptr && RNG::percent_chance(PERCENT_CHANCE_USE_ITEM))
  {
    CreaturePtr creature = map->get_creature(this_creature_id);

    if (creature != nullptr)
    {
      const list<ItemPtr>& items = creature->get_inventory()->get_items_ref();

      for (auto item : items)
      {
        if (item != nullptr)
        {
          ItemType itype = item->get_type();

          if (itype == ItemType::ITEM_TYPE_WEAPON)
          {
            use_cmd = get_equip_weapon_decision(creature, item);
          }
          else if (itype == ItemType::ITEM_TYPE_RING)
          {
            use_cmd = get_equip_ring_decision(creature, item);
          }
          else if (itype == ItemType::ITEM_TYPE_AMULET)
          {
            use_cmd = get_equip_amulet_decision(creature, item);
          }
          else if (itype == ItemType::ITEM_TYPE_AMMUNITION)
          {
            use_cmd = get_equip_ammunition_decision(creature, item);
          }
          else if (itype == ItemType::ITEM_TYPE_WAND)
          {
            use_cmd = get_use_wand_decision(creature, item, view_map);
          }
          else if (itype == ItemType::ITEM_TYPE_SPELLBOOK)
          {
            use_cmd = get_use_book_decision(creature, item);
          }

          if (use_cmd != nullptr)
          {
            return use_cmd;
          }
        }
      }
    }
  }

  return use_cmd;
}

// Get a list of the adjacent coordinates that do not contain creatures
vector<Coordinate> NPCDecisionStrategy::get_adjacent_safe_coordinates_without_creatures(MapPtr current_map, const vector<Coordinate>& all_adjacent_coordinates, CreaturePtr this_creature)
{
  CreatureTileSafetyChecker safety_checker;
  vector<Coordinate> coords_without_creatures;
  
  for (const Coordinate& c : all_adjacent_coordinates)
  {
    // Don't move if there's a creature on that coordinate.
    TilePtr adjacent_tile = current_map->at(c.first, c.second);

    if (adjacent_tile != nullptr)
    {
      if (adjacent_tile->has_creature() || (!safety_checker.is_tile_safe_for_creature(this_creature, adjacent_tile)))
      {
        continue;
      }
      else
      {
        coords_without_creatures.push_back(c);
      }
    }
  }
  
  return coords_without_creatures;
}

bool NPCDecisionStrategy::has_movement_orders() const
{
  string follow = get_property(DecisionStrategyProperties::DECISION_STRATEGY_FOLLOW_CREATURE_ID);

  bool has_orders = (!follow.empty());
  return has_orders;
}

CommandPtr NPCDecisionStrategy::get_follow_direction(MapPtr view_map, CreaturePtr this_creature, const Coordinate& this_creature_coords, const string& follow_id)
{
  CommandPtr command;
  Coordinate c_follow = view_map->get_location(follow_id);

  if (!CoordUtils::are_coordinates_adjacent(this_creature_coords, c_follow))
  {
    SearchStrategyPtr ss = SearchStrategyFactory::create_search_strategy(SearchType::SEARCH_TYPE_UNIFORM_COST, this_creature);
    Direction direction = CoordUtils::get_direction(this_creature_coords, ss->search(view_map, this_creature_coords, c_follow));

    if (direction != Direction::DIRECTION_NULL)
    {
      command = std::make_unique<MovementCommand>(direction, -1);
    }
  }

  return command;
}

void NPCDecisionStrategy::update_threats_to_leader(const std::string& this_creature_id, MapPtr view_map)
{
  Game& game = Game::instance();
  MapPtr current_map = game.get_current_map();

  if (current_map != nullptr)
  {
    CreaturePtr this_creature = current_map->get_creature(this_creature_id);

    if (this_creature != nullptr)
    {
      // Have we been ordered to attack by our leader? If so, find all the
      // threats to that creature, and attack one.
      string attack_threaten_id = get_property(DecisionStrategyProperties::DECISION_STRATEGY_ATTACK_CREATURES_THREATENING_ID);
      string leader_id = this_creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LEADER_ID);

      if (view_map != nullptr && !attack_threaten_id.empty())
      {
        CreatureMap creatures = view_map->get_creatures();
        vector<string> leader_attackers;

        for (auto c_pair : creatures)
        {
          if (c_pair.second->get_decision_strategy()->get_threats_ref().has_threat(leader_id).first)
          {
            string threat_id = c_pair.second->get_id();
            if (!threat_ratings.has_threat(threat_id).first)
            {
              HostilityManager hm;
              hm.set_hostility_to_creature(this_creature, threat_id);
            }

            // Break so that the creature is only focused on one creature
            // attacking their leader at a time.
            break;
          }
        }
      }
    }
  }
}

vector<pair<string, int>> NPCDecisionStrategy::get_creatures_by_distance(CreaturePtr creature, MapPtr view_map, const set<string>& creature_ids)
{
  vector<pair<string, int>> cdist;

  if (creature != nullptr && view_map != nullptr)
  {
    Coordinate cr_coord = view_map->get_location(creature->get_id());

    for (const string& cr_id : creature_ids)
    {
      if (view_map->has_location(cr_id))
      {
        Coordinate threat_coord = view_map->get_location(cr_id);
        cdist.push_back(make_pair(cr_id, CoordUtils::chebyshev_distance(cr_coord, threat_coord)));
      }
    }

    std::sort(cdist.begin(), cdist.end(), [](const auto& c1, const auto& c2) { return (c1.second < c2.second); });
  }

  return cdist;
}

CommandPtr NPCDecisionStrategy::get_pick_up_weapon_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && item != nullptr)
  {
    if (should_equip_weapon(creature, item))
    {
      pu_cmd = make_unique<PickUpCommand>(item->get_id());
    }
  }

  return pu_cmd;
}

CommandPtr NPCDecisionStrategy::get_pick_up_amulet_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && item != nullptr)
  {
    AmuletPtr amulet = std::dynamic_pointer_cast<Amulet>(item);

    if (amulet != nullptr)
    {
      ItemPtr amulet_eq = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_NECK);

      if (amulet_eq == nullptr && amulet->get_is_good())
      {
        pu_cmd = make_unique<PickUpCommand>(amulet->get_id());
      }
    }
  }

  return pu_cmd;
}

CommandPtr NPCDecisionStrategy::get_pick_up_ring_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && item != nullptr)
  {
    RingPtr ring = std::dynamic_pointer_cast<Ring>(item);

    if (ring != nullptr)
    {
      ItemPtr f1 = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER);
      ItemPtr f2 = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER);

      if ((f1 == nullptr || f2 == nullptr) && ring->get_is_good())
      {
        pu_cmd = make_unique<PickUpCommand>(ring->get_id());
      }
    }
  }

  return pu_cmd;
}

CommandPtr NPCDecisionStrategy::get_pick_up_ammunition_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;

  if (creature != nullptr && item != nullptr)
  {
    WeaponManager wm;
    WeaponPtr ranged = std::dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON));
    WeaponPtr ammo = std::dynamic_pointer_cast<Weapon>(item);

    if (wm.is_ranged_weapon_skill_type_compatible_with_ammunition(ranged, ammo))
    {
      pu_cmd = make_unique<PickUpCommand>(item->get_id());
    }
  }

  return pu_cmd;
}

CommandPtr NPCDecisionStrategy::get_pick_up_wand_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;
  CurrentCreatureAbilities cca;

  // Creatures only pick up wands if they can speak - otherwise, evoking won't
  // work.
  if (creature != nullptr && item != nullptr && cca.can_speak(creature))
  {
    if (item && item->get_type() == ItemType::ITEM_TYPE_WAND)
    {
      Wand* wand = dynamic_cast<Wand*>(item.get());

      if (wand->get_charges().get_current() > 0 && wand->get_has_damage())
      {
        pu_cmd = make_unique<PickUpCommand>(wand->get_id());
      }
    }
  }

  return pu_cmd;
}

CommandPtr NPCDecisionStrategy::get_pick_up_book_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr pu_cmd;
  CurrentCreatureAbilities cca;

  // Creatures only pick up wands if they can speak - otherwise, evoking won't
  // work.
  if (creature != nullptr && item != nullptr && cca.can_speak(creature))
  {
    if (item && item->get_type() == ItemType::ITEM_TYPE_SPELLBOOK)
    {
      Spellbook* book = dynamic_cast<Spellbook*>(item.get());
      if (CreatureUtils::has_skill_for_spell(creature, book->get_spell_id()))
      {
        pu_cmd = make_unique<PickUpCommand>(book->get_id());
      }
    }
  }

  return pu_cmd;
}
CommandPtr NPCDecisionStrategy::get_equip_weapon_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr equip_cmd;

  if (creature != nullptr && item != nullptr && should_equip_weapon(creature, item))
  {
    equip_cmd = make_unique<InventoryCommand>(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED, item);
  }

  return equip_cmd;
}



bool NPCDecisionStrategy::should_equip_weapon(CreaturePtr creature, ItemPtr item)
{
  bool should_eq = false;

  WeaponManager wm;
  WeaponPtr weapon = std::dynamic_pointer_cast<Weapon>(item);
  WeaponPtr eq_weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY);
  Damage d = wm.get_damage(creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY);

  if (eq_weapon == nullptr && weapon != nullptr && (weapon->get_damage().avg() > d.avg()))
  {
    should_eq = true;
  }

  return should_eq;
}

CommandPtr NPCDecisionStrategy::get_equip_ring_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr equip_cmd;

  if (creature != nullptr && item != nullptr)
  {
    Equipment& eq = creature->get_equipment();

    EquipmentWornLocation f1 = EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER;
    EquipmentWornLocation f2 = EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER;
    EquipmentWornLocation ewl = item->get_worn_location();

    if (ewl == f1 || ewl == f2)
    {
      bool f1_worn = eq.has_item(f1);
      bool f2_worn = eq.has_item(f2);

      if (!f1_worn)
      {
        equip_cmd = std::make_unique<InventoryCommand>(f1, item);
      }
      else if (!f2_worn)
      {
        equip_cmd = std::make_unique<InventoryCommand>(f2, item);
      }
    }
  }

  return equip_cmd;
}

CommandPtr NPCDecisionStrategy::get_equip_amulet_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr equip_cmd;

  if (creature != nullptr && item != nullptr)
  {
    EquipmentWornLocation ewl = item->get_worn_location();
    EquipmentWornLocation worn_loc = EquipmentWornLocation::EQUIPMENT_WORN_NECK;

    if (ewl == worn_loc && !creature->get_equipment().has_item(worn_loc))
    {
      equip_cmd = std::make_unique<InventoryCommand>(worn_loc, item);
    }
  }

  return equip_cmd;
}

CommandPtr NPCDecisionStrategy::get_equip_ammunition_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr equip_cmd;

  if (creature != nullptr && item != nullptr)
  {
    WeaponPtr ranged = std::dynamic_pointer_cast<Weapon>(creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON));
    ItemPtr ammo_item = creature->get_equipment().get_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);

    WeaponPtr ammo = std::dynamic_pointer_cast<Weapon>(item);
    WeaponManager wm;

    if (ammo_item == nullptr && wm.is_ranged_weapon_skill_type_compatible_with_ammunition(ranged, ammo))
    {
      equip_cmd = std::make_unique<InventoryCommand>(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION, item);
    }
  }

  return equip_cmd;
}

CommandPtr NPCDecisionStrategy::get_use_wand_decision(CreaturePtr creature, ItemPtr item, MapPtr view_map)
{
  CommandPtr use_cmd;
  WandPtr wand = std::dynamic_pointer_cast<Wand>(item);

  if (wand != nullptr && wand->get_charges().get_current() > 0 && wand->get_has_damage())
  {
    uint range = wand->get_range();
    AttackNPCMagicDecision anmd;
    Spell spell;
    SpellShape ss = SpellShapeFactory::create_spell_shape(wand->get_spell_shape_type(), wand->get_radius());

    spell.set_shape(ss);
    spell.set_damage(wand->get_damage());
    spell.set_range(wand->get_range());

    // If there are hostiles in range no non-hostiles in the same,
    // use the wand.
    pair<bool, Direction> dec_details = anmd.decide(creature, view_map, spell, creature->get_decision_strategy()->get_threats_ref().get_true_threats_without_level());

    if (dec_details.first)
    {
      use_cmd = std::make_unique<EvokeCommand>(wand->get_id(), dec_details.second);
    }
  }

  return use_cmd;
}

CommandPtr NPCDecisionStrategy::get_use_book_decision(CreaturePtr creature, ItemPtr item)
{
  CommandPtr use_cmd;
  SpellbookPtr book = std::dynamic_pointer_cast<Spellbook>(item);

  if (book != nullptr && CreatureUtils::has_skill_for_spell(creature, book->get_spell_id()))
  {
    use_cmd = std::make_unique<ReadCommand>(book->get_id());
  }

  return use_cmd;

}