#include "RangedCombatEquipmentChecker.hpp"

using namespace std;

// Check to see if the creature is capable of doing ranged combat by
// performing a number of checks on their equipment, and the configuration
// thereof.
pair<bool, string> RangedCombatEquipmentChecker::can_creature_do_ranged_combat(CreaturePtr creature)
{
  pair<bool, string> ranged_combat_info;
  ranged_combat_info.first = false;

  return ranged_combat_info;
}

// Check to see if there is a ranged weapon/ammunition equipped at all.
bool RangedCombatEquipmentChecker::is_ranged_weapon_equipped(CreaturePtr creature)
{
  bool ranged_equipped = false;

  if (creature)
  {
  }

  return ranged_equipped;
}

// Get a message notifying the player that nothing has been equipped.
string RangedCombatEquipmentChecker::get_ranged_weapon_not_equipped_message() const
{
  string ranged_weapon_message;
  return ranged_weapon_message;
}

// If a ranged weapon (sling, bow, etc) has been equipped, it is useless
// unless ammunition has also been equipped.
bool RangedCombatEquipmentChecker::is_ranged_weapon_and_ammunition_equipped(CreaturePtr creature)
{
  bool ammo_equipped = false;

  if (creature)
  {
  }

  return ammo_equipped;
}

// Get a message informing the player that no ammunition has been equipped.
string RangedCombatEquipmentChecker::get_ammunition_not_equipped_message() const
{
  string ammo_message;
  return ammo_message;
}

// The ammunition equipped needs to match the ranged weapon.  For example,
// slings and arrows are not much use, unless one is actually Outrageous
// Fortune.
bool RangedCombatEquipmentChecker::does_ranged_weapon_match_ammunition(CreaturePtr creature)
{
  bool weapon_match = false;

  if (creature)
  {
  }

  return weapon_match;
}

// Get a message informing the player that the type of ammunition equipped
// does not match the weapon selected.
string RangedCombatEquipmentChecker::get_weapon_and_ammunition_mismatch_message() const
{
  string weapon_mismatch;
  return weapon_mismatch;
}
