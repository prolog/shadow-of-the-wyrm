#include "DefaultNPCMagicDecision.hpp"

using namespace std;

pair<bool, Direction> DefaultNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const set<string>& creature_threats) const
{
  bool decision = false;

  // JCD FIXME revisit this later and create per-effect checkers, etc
  if (caster != nullptr)
  {
    // Make sure the creature is not already affected. Also, ensure that the
    // creature doesn't actually cast anything unless there are hostiles
    // in range.
    //
    // TODO: there should be "applicability" checks for the various
    // spell effects.
    if (!caster->is_affected_by_modifier_spell(spell.get_spell_id()) &&
        !caster->get_decision_strategy()->get_threats_ref().get_true_threats_without_level().empty())
    {
      // decision = true;
    }
  }

  return make_pair(decision, Direction::DIRECTION_NULL);
}
