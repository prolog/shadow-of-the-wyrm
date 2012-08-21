#include <boost/foreach.hpp>
#include <boost/make_shared.hpp>
#include "AmmunitionSurvivalCalculator.hpp"
#include "BresenhamLine.hpp"
#include "CombatManager.hpp"
#include "Conversion.hpp"
#include "FireWeaponTileSelectionKeyboardCommandMap.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "MessageManager.hpp"
#include "RangedCombatActionManager.hpp"
#include "RangedCombatApplicabilityChecker.hpp"
#include "RNG.hpp"
#include "TileSelectionManager.hpp"

using namespace std;
using boost::make_shared;

RangedCombatActionManager::RangedCombatActionManager()
{
}

ActionCostValue RangedCombatActionManager::fire_missile(CreaturePtr creature)
{
  ActionCostValue action_cost_value = get_action_cost_value();
  MessageManager* manager = MessageManager::instance();
  
  if (creature && manager)
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
        manager->add_new_message(ranged_combat_info.second);
        manager->send();
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
  
  // We can do ranged combat.  Select the tile, and then fire.
  TileSelectionManager tsm;
  KeyboardCommandMapPtr fire_weapon_keyboard_bindings = make_shared<FireWeaponTileSelectionKeyboardCommandMap>();
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
  Game* game = Game::instance();
  
  if (creature && game)
  {
    TargetMap& tile_map = creature->get_target_map_ref();
    
    TargetMap::iterator t_it = tile_map.find(Integer::to_string(ATTACK_TYPE_RANGED));
    
    if (t_it != tile_map.end())
    {
      MapPtr current_map = game->get_current_map();
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
  
  if (target_creature)
  {
    CombatManager cm;
    cm.attack(creature, target_creature, ATTACK_TYPE_RANGED);
  }

  destroy_ammunition_or_drop_on_tile(creature, tile);
}

// Either destroy the ammunition, or drop it on the appropriate tile.
void RangedCombatActionManager::destroy_ammunition_or_drop_on_tile(CreaturePtr creature, TilePtr tile)
{
  // Drop ammo on tile, assuming the ammunition survived being fired.
  ItemManager im;
  ItemPtr ammunition = im.remove(creature, EQUIPMENT_WORN_AMMUNITION, false);
  AmmunitionSurvivalCalculator ammunition_survival_calc;
  
  if (ammunition_survival_calc.survives(creature, ammunition))
  {
    tile->get_items().add(ammunition);
  }
}

ActionCostValue RangedCombatActionManager::get_action_cost_value() const
{
  return 1;
}
