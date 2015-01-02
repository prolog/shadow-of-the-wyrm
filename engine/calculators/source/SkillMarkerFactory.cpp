#include "SkillMarkerFactory.hpp"
#include "MeleeCombatSkillMarker.hpp"
#include "RangedCombatSkillMarker.hpp"
#include "MagicalCombatSkillMarker.hpp"

SkillMarkerFactory::SkillMarkerFactory()
{
}

SkillMarkerFactory::~SkillMarkerFactory()
{
}

ISkillMarkerPtr SkillMarkerFactory::create_skill_marker(const AttackType attack_type)
{
  ISkillMarkerPtr skill_marker;

  switch(attack_type)
  {
    case AttackType::ATTACK_TYPE_MELEE_PRIMARY:
    case AttackType::ATTACK_TYPE_MELEE_SECONDARY:
    case AttackType::ATTACK_TYPE_MELEE_TERTIARY_UNARMED:
      skill_marker = std::make_shared<MeleeCombatSkillMarker>(attack_type);
      break;
    case AttackType::ATTACK_TYPE_RANGED:
      skill_marker = std::make_shared<RangedCombatSkillMarker>();
      break;
    case AttackType::ATTACK_TYPE_MAGICAL:
    default:
      skill_marker = std::make_shared<MagicalCombatSkillMarker>();
      break;
  }

  return skill_marker;
}
