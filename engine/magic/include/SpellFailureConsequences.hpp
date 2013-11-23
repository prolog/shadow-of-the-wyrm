#pragma once
#include <memory>
#include "Creature.hpp"

// Interface representing a set of possible consequences for a particular
// severity level.  For example, the most minor severity level might summon
// bats and rats, or do a little damage, while the most could summon
// dracoliches or wipe out 90% of the caster's HP and AP.
class SpellFailureConsequences
{
  public:
    // Apply some damage to the spellcaster.
    // Returns true if the spellbook is destroyed as a result.
    virtual bool damage_caster(CreaturePtr caster);

    // Inflict one or more status ailments on the caster.
    // Returns true if the spellbook is destroyed as a result.
    virtual bool inflict_status_ailments(CreaturePtr caster);

    // Summon creatures into the caster's FOV.
    // Returns true if the spellbook is destroyed as a result.
    virtual bool summon_creatures(CreaturePtr caster);

  protected:
    virtual float get_damage_pct() const = 0;
    virtual std::string get_damage_message_sid() const = 0;

    // Returns the number of potential creatures to summon (expressed as a
    // Dice object), and the vector of creature IDs that represent the 
    // possible creatures.
    virtual std::pair<Dice, std::vector<std::string>> get_summoned_creature_details() const = 0;
    virtual std::string get_summoned_creatures_message_sid() const = 0;
};

typedef std::shared_ptr<SpellFailureConsequences> SpellFailureConsequencesPtr;