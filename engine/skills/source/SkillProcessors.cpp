#include "SkillProcessors.hpp"
#include "MessageManagerFactory.hpp"
#include "SkillTextKeys.hpp"

using namespace std;

DefaultSkillProcessor::DefaultSkillProcessor(const string& new_message_sid)
: message_sid(new_message_sid)
{
}

ActionCostValue DefaultSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

  if (creature && creature->get_is_player() && map && !message_sid.empty())
  {
    IMessageManager& manager = MM::instance();

    manager.add_new_message(StringTable::get(message_sid));
    manager.send();
  }

  return acv;
}

SkillProcessorPtr DefaultSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<DefaultSkillProcessor>(message_sid);
  return proc;
}

WeaponSkillProcessor::WeaponSkillProcessor()
: DefaultSkillProcessor(SkillTextKeys::SKILL_USAGE_WEAPON)
{
}

SkillProcessorPtr WeaponSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<WeaponSkillProcessor>();
  return proc;
}

MagicSkillProcessor::MagicSkillProcessor()
: DefaultSkillProcessor(SkillTextKeys::SKILL_USAGE_MAGIC)
{
}

SkillProcessorPtr MagicSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<MagicSkillProcessor>();
  return proc;
}
