#include <sstream>
#include "WeaponCodexDescriber.hpp"
#include "EquipmentTextKeys.hpp"
#include "SkillTextKeys.hpp"
#include "StringTable.hpp"
#include "Weapon.hpp"
#include "Creature.hpp"

using namespace std;

WeaponCodexDescriber::WeaponCodexDescriber(ItemPtr item)
: WearableCodexDescriber(item)
{
}

string WeaponCodexDescriber::describe_for_synopsis_line() const
{
  WeaponPtr weap = dynamic_pointer_cast<Weapon>(item);
  ostringstream ss;

  if (weap != nullptr)
  {
    Skills skills;
    SkillPtr m_sk = skills.get_skill(weap->get_trained_skill());
    SkillPtr r_sk = skills.get_skill(weap->get_trained_ranged_skill());
    
    if (m_sk != nullptr && r_sk != nullptr)
    {
      ss << StringTable::get(m_sk->get_skill_name_sid()) << "/" << StringTable::get(r_sk->get_skill_name_sid());
    }
  }

  return ss.str();
}

string WeaponCodexDescriber::describe_details() const
{
  ostringstream ss;
  WeaponPtr weap = dynamic_pointer_cast<Weapon>(item);

  if (weap != nullptr)
  {
    string wear_details = WearableCodexDescriber::describe_details();

    if (!wear_details.empty())
    {
      ss << wear_details << " ";
    }

    ss << EquipmentTextKeys::get_melee_weapon_synopsis(weap); 
  }

  return ss.str();
}