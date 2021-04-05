#include <boost/algorithm/string/replace.hpp>
#include "Conversion.hpp"
#include "EquipmentTextKeys.hpp"
#include "RaceManager.hpp"
#include "TextKeys.hpp"
#include "PrimaryPhysicalAttackSpeedCalculator.hpp"
#include "StringTable.hpp"
#include "WeaponDifficultyCalculator.hpp"

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
const string EquipmentTextKeys::EQUIPMENT_RESISTS_FLAGS = "EQUIPMENT_RESISTS_FLAGS";
const string EquipmentTextKeys::EQUIPMENT_WIELDED_UNSURE = "EQUIPMENT_WIELDED_UNSURE";
const string EquipmentTextKeys::EQUIPMENT_RANGED_SYNOPSIS = "EQUIPMENT_RANGED_SYNOPSIS";
const string EquipmentTextKeys::EQUIPMENT_WEAPON_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS = "EQUIPMENT_WEAPON_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS";
const string EquipmentTextKeys::EQUIPMENT_PRIMARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS = "EQUIPMENT_PRIMARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS";
const string EquipmentTextKeys::EQUIPMENT_SECONDARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS = "EQUIPMENT_SECONDARY_MELEE_DIFFICULTY_SPEED_AND_DAMAGE_SYNOPSIS";
const string EquipmentTextKeys::EQUIPMENT_REMOVAL_CURSED = "EQUIPMENT_REMOVAL_CURSED";
const string EquipmentTextKeys::EQUIPMENT_MELEE_WEAPON_RANGE = "EQUIPMENT_MELEE_WEAPON_RANGE";

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

  vector<string> dmg_flags;  
  vector<string> slays = damage.get_slays_races();
  ostringstream ss;

  if (damage.get_chaotic())
  {
    dmg_flags.push_back(TextKeys::DAMAGE_CHAOTIC);
  }

  if (damage.get_vorpal())
  {
    dmg_flags.push_back(TextKeys::DAMAGE_VORPAL);
  }

  if (damage.get_draining())
  {
    dmg_flags.push_back(TextKeys::DAMAGE_DRAINING);
  }

  if (damage.get_ethereal())
  {
    dmg_flags.push_back(TextKeys::DAMAGE_ETHEREAL);
  }

  if (damage.get_piercing())
  {
    dmg_flags.push_back(TextKeys::DAMAGE_PIERCING);
  }

  if (damage.get_incorporeal())
  {
    dmg_flags.push_back(TextKeys::DAMAGE_INCORPOREAL);
  }

  if (damage.get_scything())
  {
    dmg_flags.push_back(TextKeys::DAMAGE_SCYTHING);
  }

  if (damage.get_explosive())
  {
    dmg_flags.push_back(TextKeys::DAMAGE_EXPLOSIVE);
  }

  bool has_slays = !slays.empty();

  if (!dmg_flags.empty() || !slays.empty())
  {
    ss << " (";
    
    if (!dmg_flags.empty())
    {
      for (size_t i = 0; i < dmg_flags.size(); i++)
      {
        ss << StringTable::get(dmg_flags[i]);

        if (i != dmg_flags.size() - 1 || has_slays)
        {
          ss << ", ";
        }
      }
    }

    if (has_slays)
    {
      RaceManager rm;
      size_t ssz = slays.size();
      ss << StringTable::get(TextKeys::DAMAGE_SLAYS) << ": ";

      for (size_t i = 0; i < ssz; i++)
      {
        string slay_race_id = slays[i];
        string slay_sid;

        if (slay_race_id == "*")
        {
          slay_sid = TextKeys::EVERYTHING;
        }
        else
        {
          Race* slay_race = rm.get_race(slay_race_id);
          
          if (slay_race != nullptr)
          {
            slay_sid = slay_race->get_race_name_sid();
          }
        }

        ss << StringTable::get(slay_sid);

        if (i != ssz - 1)
        {
          ss << ", ";
        }
      }
    }

    ss << ")";
  }

  boost::replace_first(synopsis, "%s", ss.str());

  return synopsis;
}

string EquipmentTextKeys::get_melee_weapon_synopsis(const AttackType attack_type, WeaponPtr weapon, const int base_difficulty, const int total_difficulty, const int speed, const Damage& damage, const int range)
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

  string dmg_synopsis = get_weapon_difficulty_speed_and_damage_synopsis(base_difficulty, total_difficulty, speed, damage);
  boost::replace_first(synopsis, "%s", dmg_synopsis);

  string range_s = StringTable::get(EquipmentTextKeys::EQUIPMENT_MELEE_WEAPON_RANGE);
  boost::replace_first(range_s, "%s", std::to_string(range));
  synopsis = synopsis + " " + range_s;

  return synopsis;
}

// Used for the codex.  
string EquipmentTextKeys::get_melee_weapon_synopsis(WeaponPtr weapon)
{
  string synopsis;

  if (weapon != nullptr)
  {
    WeaponDifficultyCalculator wdc;
    PrimaryPhysicalAttackSpeedCalculator ppasc;

    Damage damage = weapon->get_damage();
    int damage_bonus = weapon->get_addl_damage();
    damage.set_modifier(damage.get_modifier() + damage_bonus);

    synopsis = StringTable::get(TextKeys::GENERIC_MESSAGE);
    string dmg_synopsis = get_weapon_difficulty_speed_and_damage_synopsis(weapon->get_difficulty(), wdc.get_item_total_difficulty_for_weapon(weapon), weapon->get_speed(), damage);
    boost::replace_first(synopsis, "%s", dmg_synopsis);

    int melee_range = weapon->get_range();
    string range = StringTable::get(EquipmentTextKeys::EQUIPMENT_MELEE_WEAPON_RANGE);
    boost::replace_first(range, "%s", std::to_string(melee_range));

    synopsis = synopsis + " " + range;
  }

  return synopsis;
}