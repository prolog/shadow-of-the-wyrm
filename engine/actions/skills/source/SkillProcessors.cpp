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
  ActionCostValue acv = -1;

  if (creature && creature->get_is_player() && map && !message_sid.empty())
  {
    IMessageManager& manager = MessageManagerFactory::instance();

    manager.add_new_message(StringTable::get(message_sid));
    manager.send();
  }

  return acv;
}

WeaponSkillProcessor::WeaponSkillProcessor()
: DefaultSkillProcessor(SkillTextKeys::SKILL_USAGE_WEAPON)
{
}

MagicSkillProcessor::MagicSkillProcessor()
: DefaultSkillProcessor(SkillTextKeys::SKILL_USAGE_MAGIC)
{
}
