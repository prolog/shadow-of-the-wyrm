#include "SkillProcessors.hpp"
#include "HidingSkillProcessor.hpp"
#include "MessageManagerFactory.hpp"
#include "SkillTextKeys.hpp"

using namespace std;

void PassiveSkillsProcessor::process_passive_skills(CreaturePtr creature, MapPtr map)
{
  // Sorry, NPCs, player-only (for now?)
  // Skills should also not auto-trigger on the world map.
  if (map != nullptr && 
      map->get_map_type() != MapType::MAP_TYPE_WORLD && 
      creature != nullptr && 
      creature->get_is_player())
  {
    Skills& skills = creature->get_skills();

    // Right now, the only skill that's procesed once per turn, for free,
    // is Hiding.
    if (skills.get_value(SkillType::SKILL_GENERAL_HIDING) > 0)
    {
      HidingSkillProcessor hsp;
      hsp.process(creature, map);
    }
  }
}

DefaultSkillProcessor::DefaultSkillProcessor(const string& new_message_sid, const bool new_implemented)
: message_sid(new_message_sid), implemented(new_implemented)
{
}

ActionCostValue DefaultSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

  if (creature && creature->get_is_player() && map && !message_sid.empty())
  {
    IMessageManager& manager = MMF::instance();

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

bool DefaultSkillProcessor::is_skill_implemented() const
{
  return implemented;
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
