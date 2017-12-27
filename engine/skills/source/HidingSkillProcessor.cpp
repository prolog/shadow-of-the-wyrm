#include "HidingSkillProcessor.hpp"
#include "HidingCalculator.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"

using std::string;

ActionCostValue HidingSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

  if (creature != nullptr)
  {
    if (creature->get_hidden())
    {
      add_already_hidden_message(creature);
    }
    else
    {
      HidingCalculator hc;
      string message;
      bool is_player = creature->get_is_player();

      if (RNG::percent_chance(hc.calculate_pct_chance_hide(creature, map)))
      {
        message = ActionTextKeys::get_hide_message(creature->get_description_sid(), is_player);
        creature->set_hidden(true);
      }
      else
      {
        message = ActionTextKeys::get_hide_failure_message(creature->get_description_sid(), is_player);
      }

      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, is_player);
      manager.add_new_message(message);
      manager.send();

      acv = get_default_skill_action_cost_value(creature);
    }
  }

  return acv;
}

void HidingSkillProcessor::add_already_hidden_message(CreaturePtr creature)
{
  if (creature != nullptr)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature->get_is_player());
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ALREADY_HIDDEN));
    manager.send();
  }
}