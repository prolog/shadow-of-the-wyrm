#include "ClassManager.hpp"
#include "CreaturePietyCalculator.hpp"

using namespace std;

// If a creature has 100 Religion, they would get a multiplier/divisor of
// 3.  etc.
float CreaturePietyCalculator::calculate_piety_multiplier(CreaturePtr creature)
{
  float mult = 1.0f;

  if (creature != nullptr)
  {
    mult = mult + static_cast<float>(creature->get_skills().get_value(SkillType::SKILL_GENERAL_RELIGION) * 0.02);
  }

  return mult;
}

int CreaturePietyCalculator::calculate_piety_regen_bonus(CreaturePtr creature)
{
  int piety_regen_bonus = 0;

  if (creature != nullptr)
  {
    ClassManager cm;
    Religion& religion = creature->get_religion_ref();
    string deity_id = religion.get_active_deity_id();
    DeityStatus deity_status = religion.get_deity_status(deity_id);

    Class* cur_class = cm.get_class(creature->get_class_id());

    if (cur_class)
    {
      piety_regen_bonus = cur_class->get_piety_regen_bonus();
    }

    DeityRelations& dr = religion.get_deity_relations_ref();
    auto dr_it = dr.find(religion.get_active_deity_id());

    if (dr_it != dr.end())
    {
      DeityStatus& ds = dr_it->second;
      piety_regen_bonus += ds.get_piety_regen_bonus();
    }
  }

  return piety_regen_bonus;
}
