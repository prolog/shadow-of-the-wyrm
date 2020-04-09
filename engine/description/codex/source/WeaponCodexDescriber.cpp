#include <sstream>
#include "WeaponCodexDescriber.hpp"
#include "EquipmentTextKeys.hpp"
#include "SkillTextKeys.hpp"
#include "StringTable.hpp"
#include "Weapon.hpp"
#include "Creature.hpp"

using namespace std;

WeaponCodexDescriber::WeaponCodexDescriber(WeaponPtr new_weapon)
: WearableCodexDescriber(new_weapon), weapon(new_weapon)
{
}

string WeaponCodexDescriber::describe_for_synopsis_line() const
{
  ostringstream ss;

  if (weapon != nullptr)
  {
    Skills skills;
    Skill* m_sk = skills.get_skill(weapon->get_trained_skill());
    Skill* r_sk = skills.get_skill(weapon->get_trained_ranged_skill());
    
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

  if (weapon != nullptr)
  {
    string wear_details = WearableCodexDescriber::describe_details();

    if (!wear_details.empty())
    {
      ss << wear_details << " ";
    }

    ss << EquipmentTextKeys::get_melee_weapon_synopsis(weapon); 
  }

  return ss.str();
}
