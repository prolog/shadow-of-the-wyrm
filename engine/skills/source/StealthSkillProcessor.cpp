#include "StealthSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "SkillManager.hpp"

using std::string;

ActionCostValue StealthSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = get_default_skill_action_cost_value(creature);

  if (creature && creature->get_hidden())
  {
    creature->decrement_free_hidden_actions();

    SkillManager sm;
    sm.mark_skill_with_probability(10, creature, SkillType::SKILL_GENERAL_STEALTH, true);

    // If no longer hidden, add an appropriate message.
    if (!creature->get_hidden())
    {
      bool is_player = creature->get_is_player();
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, is_player);
      string message = ActionTextKeys::get_reveal_message(creature->get_description_sid(), is_player);
      manager.add_new_message(message);
      manager.send();
    }
  }

  return acv;
}

