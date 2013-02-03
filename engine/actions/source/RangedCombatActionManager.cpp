#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "AmmunitionSurvivalCalculator.hpp"
#include "BresenhamLine.hpp"
#include "CombatManager.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "FireWeaponTileSelectionKeyboardCommandMap.hpp"
#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "ItemManager.hpp"
#include "MapCursor.hpp"
#include "MessageManager.hpp"
#include "RangedCombatActionManager.hpp"
#include "RangedCombatApplicabilityChecker.hpp"
#include "RNG.hpp"
#include "TileSelectionManager.hpp"

using namespace std;

RangedCombatActionManager::RangedCombatActionManager()
{
}

bool RangedCombatActionManager::operator==(const RangedCombatActionManager& rcam)
{
  return true;
}

ActionCostValue RangedCombatActionManager::fire_missile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = 0;
  MessageManager& manager = MessageManager::instance();
  
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
ActionCostValue RangedCombatActionManager::get_selected_tile(CreaturePtr creature)
{
  ActionCostValue action_cost_value;
  Game& game = Game::instance();
  
  // We can do ranged combat.  
  //
  // First, check to see if the creature is the player.  If the creature is the player, then check to 
  // see if a ranged target has been defined.  If not, select the closest hostile creature.
  if (creature && creature->get_is_player())
  {
    if (!has_ranged_combat_target(creature))
    {
      select_nearest_hostile_target(creature, game.get_current_map());
    }
    else
    {
      select_existing_target(creature, game.get_current_map());
    }
  }
  
  //Select the tile, and then fire.
  TileSelectionManager tsm;
  KeyboardCommandMapPtr fire_weapon_keyboard_bindings = boost::make_shared<FireWeaponTileSelectionKeyboardCommandMap>();
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
void RangedCombatActionManager::fire_weapon_at_tile(CreaturePtr creature)
{
  Game& game = Game::instance();
  
  if (creature)
  {
    TargetMap& tile_map = creature->get_target_map_ref();
    
    TargetMap::iterator t_it = tile_map.find(Integer::to_string(ATTACK_TYPE_RANGED));
    
    if (t_it != tile_map.end())
    {
      MapPtr current_map = game.get_current_map();
      pair<string, Coordinate> target_info = t_it->second;
      Coordinate creature_coords = current_map->get_location(creature->get_id());
      Coordinate target_coords = target_info.second;
      
      target_coords = get_actual_coordinates_given_missile_path(creature_coords, target_coords, current_map);
      fire_at_given_coordinates(creature, current_map, target_coords);
    }
  }
}

// Get the actual coordinates to fire at, given the missile's flight path.
Coordinate RangedCombatActionManager::get_actual_coordinates_given_missile_path(const Coordinate& creature_coords, const Coordinate& target_coords, MapPtr current_map)
{
  Coordinate target_c = target_coords;

  BresenhamLine bl;
  vector<Coordinate> line_points = bl.get_points_in_line(creature_coords.first, creature_coords.second, target_coords.first, target_coords.second);
    
  TilePtr tile;
  BOOST_FOREACH(const Coordinate& c, line_points)
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
      target_c = c;
      break;
    }
    else if (tile && (tile->has_blocking_feature()))
    {
      // Done - don't consider any other tiles.  Use the previous for dropping ammo.
      break;
    }
    else
    {
      // Update the target coordinates to the current tile's.
      target_c = c;
    }
  }
  
  return target_c;
}

// Fire at the given coordinates: attack the creature, if it is there,
// and check to see if the ammunition survives.
void RangedCombatActionManager::fire_at_given_coordinates(CreaturePtr creature, MapPtr current_map, const Coordinate& target_coords)
{
  TilePtr tile = current_map->at(target_coords);
  CreaturePtr target_creature = tile->get_creature();

  add_ranged_combat_message(creature, target_creature);
    
  if (target_creature)
  {
    CombatManager cm;
    cm.attack(creature, target_creature, ATTACK_TYPE_RANGED);
  }

  destroy_ammunition_or_drop_on_tile(creature, tile);
}

// Add an appropriate ranged combat message based on creature details, weapon details, etc.
void RangedCombatActionManager::add_ranged_combat_message(CreaturePtr creature, CreaturePtr target_creature)
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
    string usage_description_sid = item_id.get_appropriate_usage_description_sid(item->get_base_id());
    
    // Another sanity check - every item should have a usage description string ID.
    if (!usage_description_sid.empty())
    {
      // Add a message based on whether:
      // - the attacking creature is the player
      // - a launcher/ranged weapon (bow, crossbow, etc) is used
      // - target creature (may be empty - it's perfectly legitimate to target a random tile!)
      string ranged_attack_message = CombatTextKeys::get_ranged_attack_message(creature->get_is_player(), ranged, StringTable::get(creature->get_description_sid()), StringTable::get(usage_description_sid), StringTable::get(target_creature_desc_sid));

      if (!ranged_attack_message.empty())
      {
        MessageManager& manager = MessageManager::instance();
        manager.add_new_message(ranged_attack_message);
        manager.send();
      }
    }
  }
}

// Either destroy the ammunition, or drop it on the appropriate tile.
void RangedCombatActionManager::destroy_ammunition_or_drop_on_tile(CreaturePtr creature, TilePtr tile)
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
      ammunition = ItemPtr(ammunition->clone_with_new_id());
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
      Inventory& inv = tile->get_items();
      
      inv.merge_or_add(ammunition, INVENTORY_ADDITION_FRONT);
    }
  }
}

bool RangedCombatActionManager::has_ranged_combat_target(CreaturePtr creature)
{
  bool has_target = false;
  
  if (creature)
  {
    TargetMap tmap = creature->get_target_map();
    return (tmap.find(Integer::to_string(ATTACK_TYPE_RANGED)) != tmap.end());
  }
  
  return has_target;
}

// select the nearest hostile target for the initial cursor location - this is done so that the user has to do less
// to select a target, and "nearest hostile" is a good enough heuristic, for now.
void RangedCombatActionManager::select_nearest_hostile_target(CreaturePtr creature, MapPtr map)
{
  if (creature && map)
  {
    string creature_id = creature->get_id();
    MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();
    Coordinate creature_location = map->get_location(creature->get_id());
    
    // Sort hostile creatures by location.  Since this is a regular map, there is only one creature allowed per
    // distance - so if there are several distance-1 creatures, only one will be chosen for the map.
    std::map<int, pair<string, Coordinate> > hostile_creature_distance_map;
    
    if (fov_map)
    {
      std::map<string, CreaturePtr>& creatures = fov_map->get_creatures_ref();
      
      for (std::map<string, CreaturePtr>::iterator c_it = creatures.begin(); c_it != creatures.end(); c_it++)
      {
        CreaturePtr potential_target_creature = c_it->second;
        string potential_creature_id = potential_target_creature->get_id();
        
        // Is the creature not the creature doing ranged combat?  Because targetting one's self
        // would be unfortunate.
        if (potential_target_creature && (potential_creature_id != creature_id))
        {
          // Get the potential target's coordinate from the main map, using its creature ID.
          Coordinate c = map->get_location(c_it->first);

          // Is the creature hostile towards the ranged combat creature?
          ThreatRatings& threat_ratings = potential_target_creature->get_decision_strategy()->get_threats_ref();
          
          if (threat_ratings.has_threat(creature_id))
          {
            int distance = CoordUtils::chebyshev_distance(creature_location, c);
            hostile_creature_distance_map.insert(make_pair(distance, make_pair(potential_creature_id, c)));
          }
        }
      }
    }
    
    // We may by this point have the nearest hostile creature:
    if (!hostile_creature_distance_map.empty())
    {
      pair<string, Coordinate> target_creature_details = hostile_creature_distance_map.begin()->second;
      Coordinate target_coordinates = target_creature_details.second;
      
      // Set it in the targetting map attached to the creature:
      TargetMap& target_map = creature->get_target_map_ref();
      target_map[Integer::to_string(ATTACK_TYPE_RANGED)] = target_creature_details;

      // Set it on the actual map:
      MapCursor mc;
      mc.set_cursor_location(map, target_coordinates);
    }
  }
}

// Select an existing target.  Because creatures can move about after the target was previously
// acquired, update the target (if necessary) to reflect the creature's current position on the
// map.
void RangedCombatActionManager::select_existing_target(CreaturePtr creature, MapPtr map)
{
  if (creature && map && has_ranged_combat_target(creature))
  {
    // Set the target:
    string ranged_s = Integer::to_string(ATTACK_TYPE_RANGED);
    TargetMap& target_map = creature->get_target_map_ref();
    TargetMap::iterator t_it = target_map.find(ranged_s);
    pair<string, Coordinate>& target_details = t_it->second;
    string creature_id = target_details.first;
    
    MapCursor mc;
    
    if (map->has_location(creature_id))
    {
      Coordinate creature_loc = map->get_location(creature_id);
      target_details.second = creature_loc; // Ensure the location of the creature is up to date!
      mc.set_cursor_location(map, creature_loc);
    }
    else
    {
      target_map.erase(t_it);
      mc.reset_cursor(map);
    }
  }
}

ActionCostValue RangedCombatActionManager::get_action_cost_value() const
{
  return 1;
}
