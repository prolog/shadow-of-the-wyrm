#include "Game.hpp"
#include "RangedCombatApplicabilityChecker.hpp"
#include "StringTable.hpp"

using namespace std;

// Check to see if the creature is capable of doing ranged combat by
// performing a number of checks on their equipment, and the configuration
// thereof.
pair<bool, string> RangedCombatApplicabilityChecker::can_creature_do_ranged_combat(CreaturePtr creature)
{
  pair<bool, string> ranged_combat_info;
  ranged_combat_info.first = false;
  
  if (!is_current_map_type_not_world())
  {
    ranged_combat_info.second = get_ranged_combat_on_world_map_not_allowed_message();
  }
  else if (!is_ranged_weapon_equipped(creature))
  {
    ranged_combat_info.second = get_ranged_weapon_not_equipped_message();
  }
  else if (!is_ranged_weapon_and_ammunition_equipped(creature))
  {
    ranged_combat_info.second = get_ammunition_not_equipped_message();
  }
  else if (!does_ranged_weapon_match_ammunition(creature))
  {
    ranged_combat_info.second = get_weapon_and_ammunition_mismatch_message();
  }
  else
  {
    // Everything is good - update the pair so that the "success"
    // boolean value is true.
    ranged_combat_info.first = true;
  }

  return ranged_combat_info;
}

// Check to see if the type of the current map is not world.  Ranged combat isn't really
// applicable on the overworld map.
bool RangedCombatApplicabilityChecker::is_current_map_type_not_world()
{
  Game* game = Game::instance();
  bool current_map_is_not_world = false;

  current_map_is_not_world = (game && !(game->get_current_map()->get_map_type() == MAP_TYPE_WORLD));
  
  return current_map_is_not_world;
}

// Get the message that ranged combat is not allowed on the world map.
string RangedCombatApplicabilityChecker::get_ranged_combat_on_world_map_not_allowed_message() const
{
  string combat_not_allowed = StringTable::get(RangedCombatTextKeys::RANGED_COMBAT_UNAVAILABLE_ON_WORLD_MAP);
  return combat_not_allowed;
}

// Check to see if there is a ranged weapon/ammunition equipped at all.
bool RangedCombatApplicabilityChecker::is_ranged_weapon_equipped(CreaturePtr creature)
{
  if (creature)
  {
    Equipment& equipment = creature->get_equipment();
    
    ItemPtr ranged_weapon = equipment.get_item(EQUIPMENT_WORN_RANGED_WEAPON);
    ItemPtr ammunition = equipment.get_item(EQUIPMENT_WORN_AMMUNITION);
    
    if (!(ranged_weapon || ammunition))
    {
      return false;
    }    
  }

  return true;
}

// Get a message notifying the player that nothing has been equipped.
string RangedCombatApplicabilityChecker::get_ranged_weapon_not_equipped_message() const
{
  string ranged_weapon_message = StringTable::get(RangedCombatTextKeys::RANGED_COMBAT_WEAPON_NOT_EQUIPPED);
  return ranged_weapon_message;
}

// If a ranged weapon (sling, bow, etc) has been equipped, it is useless
// unless ammunition has also been equipped.
bool RangedCombatApplicabilityChecker::is_ranged_weapon_and_ammunition_equipped(CreaturePtr creature)
{
  if (creature)
  {
    Equipment& equipment = creature->get_equipment();    
    ItemPtr ammunition = equipment.get_item(EQUIPMENT_WORN_AMMUNITION);
    
    return (ammunition);
  }

  return false;
}

// Get a message informing the player that no ammunition has been equipped.
string RangedCombatApplicabilityChecker::get_ammunition_not_equipped_message() const
{
  string ammo_message = StringTable::get(RangedCombatTextKeys::RANGED_COMBAT_AMMUNITION_NOT_EQUIPPED);
  return ammo_message;
}

// The ammunition equipped needs to match the ranged weapon.  For example,
// slings and arrows are not much use, unless one is actually Outrageous
// Fortune.
bool RangedCombatApplicabilityChecker::does_ranged_weapon_match_ammunition(CreaturePtr creature)
{
  bool weapon_match = false;

  if (creature)
  {
    // JCD FIXME implement this :)
  }

  return weapon_match;
}

// Get a message informing the player that the type of ammunition equipped
// does not match the weapon selected.
string RangedCombatApplicabilityChecker::get_weapon_and_ammunition_mismatch_message() const
{
  string weapon_mismatch = StringTable::get(RangedCombatTextKeys::RANGED_COMBAT_WEAPON_AMMUNITION_MISMATCH);
  return weapon_mismatch;
}
