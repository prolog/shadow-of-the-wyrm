#include "Game.hpp"
#include "RangedCombatApplicabilityChecker.hpp"
#include "RangedCombatTextKeys.hpp"
#include "StringTable.hpp"
#include "WeaponManager.hpp"

using namespace std;
using std::dynamic_pointer_cast;

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
  else if (!is_ranged_weapon_required_and_equipped(creature))
  {
    ranged_combat_info.second = get_ammunition_requires_ranged_weapon_message();
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
  Game& game = Game::instance();
  bool current_map_is_not_world = false;

  current_map_is_not_world = !(game.get_current_map()->get_map_type() == MapType::MAP_TYPE_WORLD);
  
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
    
    ItemPtr ranged_weapon = equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON);
    ItemPtr ammunition = equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);
    
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
    ItemPtr ammunition = equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);
    
    return (ammunition != nullptr);
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
    Equipment& equipment = creature->get_equipment();
    
    WeaponPtr ranged_weapon = dynamic_pointer_cast<Weapon>(equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON));
    ItemPtr ammo_slot_item = equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);
    WeaponPtr ammunition = dynamic_pointer_cast<Weapon>(ammo_slot_item);
    PotionPtr potion_ammo = dynamic_pointer_cast<Potion>(ammo_slot_item);

    WeaponManager wm;
    weapon_match = ((potion_ammo && !ranged_weapon) || wm.is_ranged_weapon_skill_type_compatible_with_ammunition(ranged_weapon, ammunition));
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

// Check to see if the ammunition requires a ranged weapon.
bool RangedCombatApplicabilityChecker::is_ranged_weapon_required_and_equipped(CreaturePtr creature)
{
  bool ranged_weapon_required_and_equipped = true;
  
  if (creature)
  {
    Equipment& equipment = creature->get_equipment();
    WeaponPtr ammunition = dynamic_pointer_cast<Weapon>(equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION));
    ItemPtr ranged_weapon = equipment.get_item(EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON);

    bool ammunition_requires_ranged_weapon = false;

    if (ammunition) // may be a potion instead of just ammunition...
    {
      ammunition_requires_ranged_weapon = ammunition->get_requires_ranged_weapon();
    }
    
    if (ammunition_requires_ranged_weapon && !ranged_weapon)
    {
      ranged_weapon_required_and_equipped = false;
    }
  }
  
  return ranged_weapon_required_and_equipped;
}

string RangedCombatApplicabilityChecker::get_ammunition_requires_ranged_weapon_message() const
{
  string ammo_requires_ranged = StringTable::get(RangedCombatTextKeys::RANGED_COMBAT_AMMUNITION_REQUIRES_RANGED_WEAPON);
  return ammo_requires_ranged;
}
