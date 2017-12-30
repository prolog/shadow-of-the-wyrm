#include "StealthSkillProcessor.hpp"
#include "MessageManagerFactory.hpp"
#include "SkillManager.hpp"
#include "StatusEffectFactory.hpp"

using std::string;

ActionCostValue StealthSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = get_default_skill_action_cost_value(creature);

  if (creature && creature->has_status(StatusIdentifiers::STATUS_ID_HIDE))
  {
    creature->decrement_free_hidden_actions();

    SkillManager sm;
    sm.mark_skill_with_probability(10, creature, SkillType::SKILL_GENERAL_STEALTH, true);

    // If no longer hidden, add an appropriate message.
    if (creature->get_free_hidden_actions() == 0)
    {
      StatusEffectPtr hide = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_HIDE, creature->get_id());

      if (hide != nullptr)
      {
        hide->undo_change(creature);
      }
    }
  }

  return acv;
}

