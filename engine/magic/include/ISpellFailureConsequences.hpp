#pragma once
#include <boost/shared_ptr.hpp>
#include "Creature.hpp"

// Interface representing a set of possible consequences for a particular
// severity level.  For example, the most minor severity level might summon
// bats and rats, or do a little damage, while the most could summon
// dracoliches or wipe out 90% of the caster's HP and AP.
class ISpellFailureConsequences
{
  public:
    // Apply some damage to the spellcaster.
    virtual void damage_caster(CreaturePtr caster) = 0;

    // Inflict one or more status ailments on the caster.
    virtual void inflict_status_ailments(CreaturePtr caster) = 0;

    // Summon creatures into the caster's FOV.
    virtual void summon_creatures(CreaturePtr caster) = 0;
};

typedef boost::shared_ptr<ISpellFailureConsequences> ISpellFailureConsequencesPtr;