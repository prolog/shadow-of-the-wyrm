#include "HidingSkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"

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
      // JCD FIXME calculations
      creature->set_hidden(true);

      bool is_player = creature->get_is_player();
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, is_player);
      manager.add_new_message(ActionTextKeys::get_hide_message(creature->get_description_sid(), is_player));
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