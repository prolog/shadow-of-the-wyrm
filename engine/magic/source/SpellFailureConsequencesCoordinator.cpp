#include "MarginalSpellFailureConsequences.hpp"
#include "RNG.hpp"
#include "SevereSpellFailureConsequences.hpp"
#include "LesserSpellFailureConsequences.hpp"
#include "SpellFailureConsequencesCoordinator.hpp"
#include "SpellConstants.hpp"

// Coordinate the spell failure consequences to the caster.  Damage the caster,
// inflict status ailments, or summon creatures with equal probability.
bool SpellFailureConsequencesCoordinator::coordinate_failure_consequences(CreaturePtr caster, const int spell_failure_difference)
{
  bool spellbook_destroyed = false;
  SpellFailureConsequencesPtr consequences = create_spell_failure_consequences(spell_failure_difference);
  int rand = RNG::range(1, 3);

  switch(rand)
  {
    case 1:
      spellbook_destroyed = consequences->damage_caster(caster);
      break;
    case 2:
      spellbook_destroyed = consequences->inflict_status_ailments(caster);
      break;
    case 3:
    default:
      spellbook_destroyed = consequences->summon_creatures(caster);
      break;
  }

  return spellbook_destroyed;
}

// Create an ISpellFailureConsequences shared_ptr based on the difficulty -
// if the spell was barely failed, do nothing; if the spell was failed by a
// good margin, create a "regular" failure consequences ptr; and if it was
// failed by a huge margin (difficult spell, plus big failure), create a
// much more severe set of consequences.
SpellFailureConsequencesPtr SpellFailureConsequencesCoordinator::create_spell_failure_consequences(const int spell_failure_difference)
{
  SpellFailureConsequencesPtr consequences = std::make_shared<MarginalSpellFailureConsequences>();

  if (spell_failure_difference < SpellConstants::SPELL_FAILURE_VERY_BAD)
  {
    consequences = std::make_shared<SevereSpellFailureConsequences>();
  }
  else if (spell_failure_difference < SpellConstants::SPELL_FAILURE_BAD)
  {
    consequences = std::make_shared<LesserSpellFailureConsequences>();
  }

  return consequences;
}
