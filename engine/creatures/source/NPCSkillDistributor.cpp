#include "NPCSkillDistributor.hpp"
#include "RNG.hpp"
#include "WeaponManager.hpp"

using namespace std;

void NPCSkillDistributor::distribute_unused_skill_points(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    vector<SkillType> imp_skills = get_skills_to_improve(creature);
    Skills& sk = creature->get_skills();
    int skill_points = creature->get_skill_points();

    while (skill_points > 0 && !imp_skills.empty())
    {
      SkillType skill = imp_skills.at(RNG::range(0, imp_skills.size() - 1));
      Skill* sk = creature->get_skills().get_skill(skill);
      
      if (sk != nullptr)
      {
        int max_improve = Skills::MAX_SKILL_VALUE - sk->get_value();

        // If we've got a skill that we've improved to max, remove it.
        if (max_improve == 0)
        {
          imp_skills.erase(std::find(imp_skills.begin(), imp_skills.end(), skill));
          continue;
        }

        // ...otherwise, improve it.
        int improve_points = RNG::range(1, std::min<int>(skill_points, max_improve));
        sk->set_value(sk->get_value() + improve_points);
        skill_points -= improve_points;
      }
    }

    creature->set_skill_points(skill_points);
  }
}

vector<SkillType> NPCSkillDistributor::get_skills_to_improve(CreaturePtr creature) const
{
  vector<SkillType> skills;

  if (creature != nullptr)
  {
    Skills& sk = creature->get_skills();

    // Melee
    WeaponManager wm;
    WeaponPtr weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_MELEE_PRIMARY);
    SkillType wskill = SkillType::SKILL_MELEE_UNARMED;

    if (weapon != nullptr)
    {
      wskill = weapon->get_trained_skill();
    }

    // Ranged
    weapon = wm.get_weapon(creature, AttackType::ATTACK_TYPE_RANGED);

    if (weapon != nullptr)
    {
      skills.push_back(weapon->get_trained_ranged_skill());
    }

    // Create the check vector, check each skill, and if it's > 0 then
    // include it in the vector of skills to potentially improve.
    //
    // The exception to this is the applicable weapon/ranged skills,
    // which will always be improved.
    skills.push_back(wskill);

    vector<SkillType> check_skills = {SkillType::SKILL_GENERAL_COMBAT, 
                                      SkillType::SKILL_GENERAL_DUNGEONEERING, 
                                      SkillType::SKILL_GENERAL_INTIMIDATION,
                                      SkillType::SKILL_GENERAL_AWARENESS, 
                                      SkillType::SKILL_GENERAL_ARCHERY, 
                                      SkillType::SKILL_GENERAL_MAGIC, 
                                      SkillType::SKILL_MAGIC_ARCANE, 
                                      SkillType::SKILL_MAGIC_DIVINE, 
                                      SkillType::SKILL_MAGIC_MYSTIC, 
                                      SkillType::SKILL_MAGIC_PRIMORDIAL,
                                      SkillType::SKILL_MAGIC_CANTRIPS};

    for (SkillType st : check_skills)
    {
      if (sk.get_value(st) > 0)
      {
        skills.push_back(st);
      }
    }
  }

  return skills;
}

#ifdef UNIT_TESTS
#include "unit_tests/NPCSkillDistributor_test.cpp"
#endif