#include <boost/make_shared.hpp>
#include "MarginalSpellFailureConsequences.hpp"
#include "RNG.hpp"
#include "SevereSpellFailureConsequences.hpp"
#include "SpellFailureConsequences.hpp"
#include "SpellFailureConsequencesCoordinator.hpp"
#include "SpellConstants.hpp"

// Coordinate the spell failure consequences to the caster.  Damage the caster,
// inflict status ailments, or summon creatures with equal probability.
void SpellFailureConsequencesCoordinator::coordinate_failure_consequences(CreaturePtr caster, const int spell_failure_difference)
{
  ISpellFailureConsequencesPtr consequences = create_spell_failure_consequences(spell_failure_difference);
  int rand = RNG::range(1, 3);

  switch(rand)
  {
    case 1:
      consequences->damage_caster(caster);
      break;
    case 2:
      consequences->inflict_status_ailments(caster);
      break;
    case 3:
    default:
      consequences->summon_creatures(caster);
      break;
  }
}

// Create an ISpellFailureConsequences shared_ptr based on the difficulty -
// if the spell was barely failed, do nothing; if the spell was failed by a
// good margin, create a "regular" failure consequences ptr; and if it was
// failed by a huge margin (difficult spell, plus big failure), create a
// much more severe set of consequences.
ISpellFailureConsequencesPtr SpellFailureConsequencesCoordinator::create_spell_failure_consequences(const int spell_failure_difference)
{
  ISpellFailureConsequencesPtr consequences = boost::make_shared<MarginalSpellFailureConsequences>();

  if (spell_failure_difference < SpellConstants::SPELL_FAILURE_VERY_BAD)
  {
    consequences = boost::make_shared<SevereSpellFailureConsequences>();
  }
  else if (spell_failure_difference < SpellConstants::SPELL_FAILURE_BAD)
  {
    consequences = boost::make_shared<SpellFailureConsequences>();
  }

  return consequences;
}
