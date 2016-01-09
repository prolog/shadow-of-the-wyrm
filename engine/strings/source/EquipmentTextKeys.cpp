#include <boost/algorithm/string/replace.hpp>
#include "Conversion.hpp"
#include "EquipmentTextKeys.hpp"
#include "TextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

EquipmentTextKeys::EquipmentTextKeys()
{
}

const string EquipmentTextKeys::EQUIPMENT_HEAD         = "EQUIPMENT_HEAD";
const string EquipmentTextKeys::EQUIPMENT_NECK         = "EQUIPMENT_NECK";
const string EquipmentTextKeys::EQUIPMENT_RIGHT_FINGER = "EQUIPMENT_RIGHT_FINGER";
const string EquipmentTextKeys::EQUIPMENT_LEFT_FINGER  = "EQUIPMENT_LEFT_FINGER";
const string EquipmentTextKeys::EQUIPMENT_WIELDED      = "EQUIPMENT_WIELDED";
const string EquipmentTextKeys::EQUIPMENT_OFF_HAND     = "EQUIPMENT_OFF_HAND";
const string EquipmentTextKeys::EQUIPMENT_BODY         = "EQUIPMENT_BODY";
const string EquipmentTextKeys::EQUIPMENT_AROUND_BODY  = "EQUIPMENT_AROUND_BODY";
const string EquipmentTextKeys::EQUIPMENT_FEET         = "EQUIPMENT_FEET";
const string EquipmentTextKeys::EQUIPMENT_RANGED       = "EQUIPMENT_RANGED";
const string EquipmentTextKeys::EQUIPMENT_AMMUNITION   = "EQUIPMENT_AMMUNITION";
const string EquipmentTextKeys::EQUIPMENT_RANGED_SYNOPSIS = "EQUIPMENT_RANGED_SYNOPSIS";
const string EquipmentTextKeys::EQUIPMENT_WEAPON_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS = "EQUIPMENT_WEAPON_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS";
const string EquipmentTextKeys::EQUIPMENT_PRIMARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS = "EQUIPMENT_PRIMARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS";
const string EquipmentTextKeys::EQUIPMENT_SECONDARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS = "EQUIPMENT_SECONDARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS";
const string EquipmentTextKeys::EQUIPMENT_REMOVAL_CURSED = "EQUIPMENT_REMOVAL_CURSED";

string EquipmentTextKeys::get_equipment_text_from_given_worn_location(const EquipmentWornLocation& worn_location)
{
  string equipment_text;
  string equipment_text_sid;
  
  switch(worn_location)
  {
    case EquipmentWornLocation::EQUIPMENT_WORN_HEAD:
      equipment_text_sid = EQUIPMENT_HEAD;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_NECK:
      equipment_text_sid = EQUIPMENT_NECK;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_RIGHT_FINGER:
      equipment_text_sid = EQUIPMENT_RIGHT_FINGER;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_LEFT_FINGER:
      equipment_text_sid = EQUIPMENT_LEFT_FINGER;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_WIELDED:
      equipment_text_sid = EQUIPMENT_WIELDED;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_OFF_HAND:
      equipment_text_sid = EQUIPMENT_OFF_HAND;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_BODY:
      equipment_text_sid = EQUIPMENT_BODY;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_AROUND_BODY:
      equipment_text_sid = EQUIPMENT_AROUND_BODY;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_FEET:
      equipment_text_sid = EQUIPMENT_FEET;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_RANGED_WEAPON:
      equipment_text_sid = EQUIPMENT_RANGED;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION:
      equipment_text_sid = EQUIPMENT_AMMUNITION;
      break;
    case EquipmentWornLocation::EQUIPMENT_WORN_NONE:
    case EquipmentWornLocation::EQUIPMENT_WORN_LAST:
    default:
      break;
  }
  
  equipment_text = StringTable::get(equipment_text_sid);
  return equipment_text;
}

string EquipmentTextKeys::get_ranged_weapon_synopsis(WeaponPtr ranged_weapon, WeaponPtr ammunition, const string& difficulty_speed_and_damage_synopsis)
{
  string ranged_synopsis = StringTable::get(EQUIPMENT_RANGED_SYNOPSIS);
  string weapon_string = "/";
  string ammunition_string = "/";
  
  if (ranged_weapon)
  {
    weapon_string = StringTable::get(ranged_weapon->get_description_sid());
  }
  
  if (ammunition)
  {
    ammunition_string = StringTable::get(ammunition->get_description_sid());
  }
  
  boost::replace_first(ranged_synopsis, "%s", weapon_string);
  boost::replace_first(ranged_synopsis, "%s", ammunition_string);
  boost::replace_first(ranged_synopsis, "%s", difficulty_speed_and_damage_synopsis);
  
  return ranged_synopsis;
}

string EquipmentTextKeys::get_weapon_difficulty_speed_and_damage_synopsis(const int base_difficulty, const int total_difficulty, const int speed, const Damage& damage)
{
  string synopsis = StringTable::get(EQUIPMENT_WEAPON_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS);

  boost::replace_first(synopsis, "%s", std::to_string(base_difficulty));
  boost::replace_first(synopsis, "%s", std::to_string(total_difficulty));
  boost::replace_first(synopsis, "%s", std::to_string(speed));
  boost::replace_first(synopsis, "%s", damage.str());
  
  return synopsis;
}

string EquipmentTextKeys::get_melee_weapon_synopsis(const AttackType attack_type, WeaponPtr weapon, const int base_difficulty, const int total_difficulty, const int speed, const Damage& damage)
{
  string synopsis;
  
  if (attack_type == AttackType::ATTACK_TYPE_MELEE_PRIMARY)
  {
    synopsis = StringTable::get(EQUIPMENT_PRIMARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS);
  }
  else if (attack_type == AttackType::ATTACK_TYPE_MELEE_SECONDARY)
  {
    synopsis = StringTable::get(EQUIPMENT_SECONDARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS);
  }
  
  string weapon_description_sid = TextKeys::UNARMED;
  
  if (weapon)
  {
    weapon_description_sid = weapon->get_description_sid();
  }
  
  boost::replace_first(synopsis, "%s", StringTable::get(weapon_description_sid));
  boost::replace_first(synopsis, "%s", std::to_string(base_difficulty));
  boost::replace_first(synopsis, "%s", std::to_string(total_difficulty));
  boost::replace_first(synopsis, "%s", std::to_string(speed));
  boost::replace_first(synopsis, "%s", damage.str());
  
  return synopsis;
}
