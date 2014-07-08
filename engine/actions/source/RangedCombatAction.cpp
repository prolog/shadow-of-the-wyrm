#include "ActionTextKeys.hpp"
#include "AmmunitionSurvivalCalculator.hpp"
#include "AnimationTranslator.hpp"
#include "BresenhamLine.hpp"
#include "CombatManager.hpp"
#include "CombatTextKeys.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "FireWeaponTileSelectionKeyboardCommandMap.hpp"
#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "ItemManager.hpp"
#include "MapCursor.hpp"
#include "MapTranslator.hpp"
#include "MessageManagerFactory.hpp"
#include "QuaffAction.hpp"
#include "RangedCombatAction.hpp"
#include "RangedCombatApplicabilityChecker.hpp"
#include "RNG.hpp"
#include "SelectionUtils.hpp"
#include "TileSelectionAction.hpp"

using namespace std;

RangedCombatAction::RangedCombatAction()
{
}

bool RangedCombatAction::operator==(const RangedCombatAction& rca) const
{
  return true;
}

ActionCostValue RangedCombatAction::fire_missile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  
  if (creature)
  {
    RangedCombatApplicabilityChecker rcec;
    
    pair<bool, string> ranged_combat_info = rcec.can_creature_do_ranged_combat(creature);
    
    if (ranged_combat_info.first)
    {
      action_cost_value = get_selected_tile(creature);
      
      // If the action advances a turn, we've selected a tile:
      if (action_cost_value)
      {
        fire_weapon_at_tile(creature);
      }
    }
    else
    {
      // We are unable to do ranged combat, for some sort of reason.  Display the message
      // that was generated regarding this.
      if (creature->get_is_player())
      {
        manager.add_new_message(ranged_combat_info.second);
        manager.send();
      }
    }
  }
  
  return action_cost_value;
}

// Get the selected tile by invoking the tile selection manager.  Once this is done,
// the tile is either selected, or the action has been cancelled.
ActionCostValue RangedCombatAction::get_selected_tile(CreaturePtr creature)
{
  ActionCostValue action_cost_value;
  Game& game = Game::instance();
  
  // We can do ranged combat.  
  //
  // First, check to see if the creature is the player.  If the creature is the player, then check to 
  // see if a ranged target has been defined.  If not, select the closest hostile creature.
  if (creature && creature->get_is_player())
  {
    MapPtr current_map = game.get_current_map();

    if (!SelectionUtils::has_target(creature, ATTACK_TYPE_RANGED))
    {
      SelectionUtils::select_nearest_hostile_target(creature, current_map);
    }
    else
    {
      SelectionUtils::select_existing_target(creature, current_map);
    }
  }
  
  //Select the tile, and then fire.
  TileSelectionAction tsm;
  KeyboardCommandMapPtr fire_weapon_keyboard_bindings = std::make_shared<FireWeaponTileSelectionKeyboardCommandMap>();
  tsm.set_keyboard_command_map(fire_weapon_keyboard_bindings);
  tsm.set_show_tile_description(false);
  tsm.set_show_feature_description(false);
  tsm.set_show_item_descriptions(false);
  // Show only the creature.
  
  tsm.set_selection_key(Integer::to_string(ATTACK_TYPE_RANGED));
  
  action_cost_value = tsm.select_tile(creature, ActionTextKeys::ACTION_FIRE);  
  return action_cost_value;
}

// Fire the creature's weapon at the selected tile.
//
// Check along the line of fire to see if there is anything blocking the way,
// such as a creature, or a blocking feature.  If there is, fire at the first
// such blocking instance.
//
// JCD TODO: Checks on range of weapon.
void RangedCombatAction::fire_weapon_at_tile(CreaturePtr creature)
{
  Game& game = Game::instance();
  
  if (creature)
  {
    TargetMap& tile_map = creature->get_target_map_ref();
    
    TargetMap::iterator t_it = tile_map.find(Integer::to_string(ATTACK_TYPE_RANGED));
    DisplayTile projectile_disp = MapTranslator::create_display_tile_from_item(creature->get_equipment().get_item(EQUIPMENT_WORN_AMMUNITION));
    
    if (t_it != tile_map.end())
    {
      MapPtr current_map = game.get_current_map();
      pair<string, Coordinate> target_info = t_it->second;
      Coordinate creature_coords = current_map->get_location(creature->get_id());
      Coordinate target_coords = target_info.second;
      
      // Get the attack path so that we can determine the actual target coords,
      // and create an animation if necessary.
      vector<Coordinate> attack_path = get_actual_coordinates_given_missile_path(creature_coords, target_coords, current_map);
      vector<pair<DisplayTile, vector<Coordinate>>> animation_frames;

      for(const Coordinate& c : attack_path)
      {
        vector<Coordinate> frame;
        frame.push_back(c);
        animation_frames.push_back(make_pair(projectile_disp, frame));
      }
      
      if (!attack_path.empty())
      {
        target_coords = attack_path.back();

        DisplayPtr display = game.get_display();

        // Create the animation showing the flight of the projectile.
        AnimationTranslator anim_tr(display);
        MapPtr current_map = game.get_current_map();
        MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();
        CurrentCreatureAbilities cca;
        CreaturePtr player = game.get_current_player();

        Animation anim = anim_tr.create_movement_animation(!cca.can_see(player), game.get_current_world()->get_calendar().get_season()->get_season(), animation_frames, true, current_map, fov_map);

        display->draw_animation(anim);
      }

      // Determine whether it's a hit or miss.
      fire_at_given_coordinates(creature, current_map, target_coords);
    }
  }
}

// Get the actual coordinates to fire at, given the missile's flight path.
vector<Coordinate> RangedCombatAction::get_actual_coordinates_given_missile_path(const Coordinate& creature_coords, const Coordinate& target_coords, MapPtr current_map)
{
  vector<Coordinate> actual_coordinates;

  BresenhamLine bl;
  vector<Coordinate> line_points = bl.get_points_in_line(creature_coords.first, creature_coords.second, target_coords.first, target_coords.second);
    
  TilePtr tile;
  for(const Coordinate& c : line_points)
  {
    // Ignore the first element of the line, since it will contain the creature that's
    // actually firing the missile.
    if (c == creature_coords)
    {
      continue;
    }
    
    tile = current_map->at(c);
    
    if (tile && tile->has_creature())
    {
      // There's a creature here - use this tile for targetting/dropping ammo.
      actual_coordinates.push_back(c);
      break;
    }
    // Check to see if there's a blocking feature, or if the tile itself blocks things
    // (walls, etc).
    else if (tile && (tile->get_movement_multiplier() == 0) || (tile->has_blocking_feature()))
    {
      // Done - don't consider any other tiles.  Use the previous for dropping ammo.
      break;
    }
    else
    {
      // Update the target coordinates to the current tile's.
      actual_coordinates.push_back(c);
    }
  }
  
  return actual_coordinates;
}

// Fire at the given coordinates: attack the creature, if it is there,
// and check to see if the ammunition survives.
void RangedCombatAction::fire_at_given_coordinates(CreaturePtr creature, MapPtr current_map, const Coordinate& target_coords)
{
  bool ammo_auto_destroy = false;

  TilePtr tile = current_map->at(target_coords);
  CreaturePtr target_creature = tile->get_creature();

  add_ranged_combat_message(creature, target_creature);
    
  if (target_creature)
  {
    CombatManager cm;

    PotionPtr potion = dynamic_pointer_cast<Potion>(creature->get_equipment().get_item(EQUIPMENT_WORN_AMMUNITION));

    if (potion)
    {
      QuaffAction qa;
      qa.explode_potion(creature, target_creature, potion);

      // Potion shatters, creature is covered in it.
      ammo_auto_destroy = true;
    }
    else
    {
      cm.attack(creature, target_creature, ATTACK_TYPE_RANGED);
    }
  }

  if (!ammo_auto_destroy)
  {
    destroy_ammunition_or_drop_on_tile(creature, tile);
  }
}

// Add an appropriate ranged combat message based on creature details, weapon details, etc.
void RangedCombatAction::add_ranged_combat_message(CreaturePtr creature, CreaturePtr target_creature)
{
  string target_creature_desc_sid;
  
  // If a target creature is specified, a message is added noting that the ammunition is fired "at something".
  if (target_creature)
  {
    target_creature_desc_sid = target_creature->get_description_sid();
  }
  
  ItemPtr ranged = creature->get_equipment().get_item(EQUIPMENT_WORN_RANGED_WEAPON);
  ItemPtr item = creature->get_equipment().get_item(EQUIPMENT_WORN_AMMUNITION);
  
  // This is mostly a sanity check.  Ammunition can only be fired if there's ammunition!
  if (item)
  {
    ItemIdentifier item_id;
    string usage_description = item_id.get_appropriate_usage_description(item);
    
    // Another sanity check - every item should have a usage description string ID.
    if (!usage_description.empty())
    {
      bool target_is_player = target_creature && target_creature->get_is_player();

      // Add a message based on whether:
      // - the attacking creature is the player
      // - a launcher/ranged weapon (bow, crossbow, etc) is used
      // - target creature (may be empty - it's perfectly legitimate to target a random tile!)
      string ranged_attack_message = CombatTextKeys::get_ranged_attack_message(creature->get_is_player(), target_is_player, ranged != nullptr, StringTable::get(creature->get_description_sid()), usage_description, StringTable::get(target_creature_desc_sid));

      if (!ranged_attack_message.empty())
      {
        IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
        manager.add_new_message(ranged_attack_message);
        manager.send();
      }
    }
  }
}

// Either destroy the ammunition, or drop it on the appropriate tile.
void RangedCombatAction::destroy_ammunition_or_drop_on_tile(CreaturePtr creature, TilePtr tile)
{
  // Drop ammo on tile, assuming the ammunition survived being fired.
  ItemManager im;
  
  if (creature)
  {
    // Check to see if there is a quantity of ammunition > 1; if so, reduce the quantity by
    // 1, but don't remove it.
    Equipment& eq = creature->get_equipment();
    ItemPtr ammunition = eq.get_item(EQUIPMENT_WORN_AMMUNITION);
    
    if (ammunition->get_quantity() > 1)
    {
      // Reduce the quantity by 1.
      ammunition->set_quantity(ammunition->get_quantity() - 1);
      
      // Clone the item so that a "new" item can be added to the ground,
      // assuming the ammunition survives.
      ammunition = ItemPtr(ammunition->create_with_new_id());
      ammunition->set_quantity(1);
    }
    else
    {
      // Last ammunition - remove it from the equipment.
      ammunition = im.remove(creature, EQUIPMENT_WORN_AMMUNITION, false);
    }
    
    AmmunitionSurvivalCalculator ammunition_survival_calc;
    
    if (ammunition_survival_calc.survives(creature, ammunition))
    {
      IInventoryPtr inv = tile->get_items();
      
      inv->merge_or_add(ammunition, INVENTORY_ADDITION_FRONT);
    }
  }
}

ActionCostValue RangedCombatAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
