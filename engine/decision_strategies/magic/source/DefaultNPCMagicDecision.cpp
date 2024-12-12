#include "DefaultNPCMagicDecision.hpp"
#include "EffectFactory.hpp"
#include "EffectTypeTerrainChecker.hpp"
#include "Game.hpp"
#include "NPCEffectDeciderFactory.hpp"
#include "RNG.hpp"

using namespace std;

const int DefaultNPCMagicDecision::PCT_CHANCE_CAST_WHILE_UNDER_THREAT = 10;

pair<bool, Direction> DefaultNPCMagicDecision::decide(CreaturePtr caster, MapPtr view_map, const Spell& spell, const set<string>& /*creature_threats*/) const
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
    MapPtr current_map = Game::instance().get_current_map();
    EffectType et = spell.get_effect();
    EffectPtr effect = EffectFactory::create_effect(et, {}, {}, "", "");
    string es_id = effect != nullptr ? effect->get_status_id() : "";

    // Check to see if the creature is already affected - either by the spell
    // itself, or the underlying effect modifier (if one exists).
    if (!(caster->is_affected_by_modifier_spell(spell.get_spell_id()) ||
         (!es_id.empty() && caster->is_affected_by_modifier_spell(effect->get_status_id()))) &&
        threat_check)
    {
      INPCEffectDeciderPtr decider = NPCEffectDeciderFactory::create_effect_decider(caster, view_map, current_map, et, spell.get_shape().get_spell_shape_type(), threats_exist);

      if (decider != nullptr)
      {
        decision = decider->decide();
      }
    }
  }

  return make_pair(decision, Direction::DIRECTION_NULL);
}
