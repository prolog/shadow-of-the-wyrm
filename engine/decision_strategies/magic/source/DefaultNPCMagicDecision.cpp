#include "DefaultNPCMagicDecision.hpp"
#include "EffectTypeTerrainChecker.hpp"
#include "RNG.hpp"

using namespace std;

const int DefaultNPCMagicDecision::PCT_CHANCE_CAST_WHILE_UNDER_THREAT = 5;

pair<bool, Direction> DefaultNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const set<string>& creature_threats) const
{
  bool decision = false;

  if (caster != nullptr)
  {
    // Make sure the creature is not already affected. If there are hostile
    // creatures in range, there is a small chance the spell will be 
    // cast - generally, creatures will decide for offensive magic or
    // to attack instead.
    bool threats_exist = !caster->get_decision_strategy()->get_threats_ref().get_true_threats_without_level().empty();
    bool threat_check = !threats_exist || RNG::percent_chance(PCT_CHANCE_CAST_WHILE_UNDER_THREAT);

    if (!caster->is_affected_by_modifier_spell(spell.get_spell_id()) &&
        threat_check)
    {
      EffectType et = spell.get_effect();
      EffectTypeTerrainChecker ettc;

      decision = ettc.does_effect_match_terrain(caster, view_map, et);

      // Later: return true if decision is true, and otherwise continue
      // checking other conditions...
    }
  }

  return make_pair(decision, Direction::DIRECTION_NULL);
}
