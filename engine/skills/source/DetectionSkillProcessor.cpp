#include "ActionTextKeys.hpp"
#include "DetectionSkillProcessor.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SkillManager.hpp"

using namespace std;

ActionCostValue DetectionSkillProcessor::process(CreaturePtr creature, MapPtr map)
{  
  if (creature && map && map->get_map_type() != MapType::MAP_TYPE_WORLD) // Player's the only creature on the map in this case, so no msgs.
  {
    // Check for any out-of-depth hostile creatures.
    vector<CreaturePtr> hostile_creatures = MapUtils::get_hostile_creatures(creature->get_id(), map);
    bool ood_dangerous_hostile_exists = false;

    for (CreaturePtr hc : hostile_creatures)
    {
      if (hc)
      {
        int hostile_creature_level = hc->get_level().get_current();

        if (hostile_creature_level > map->get_danger() && hostile_creature_level > creature->get_level().get_current())
        {
          ood_dangerous_hostile_exists = true;
          break;
        }
      }
    }

    if (ood_dangerous_hostile_exists)
    {
      SkillManager sm;

      if (sm.check_skill(creature, SkillType::SKILL_GENERAL_DETECTION))
      {
        creature->get_skills().mark(SkillType::SKILL_GENERAL_DETECTION);

        IMessageManager& manager = MM::instance(MessageTransmit::MAP, creature, creature && creature->get_is_player());

        string detected_creatures = StringTable::get(ActionTextKeys::ACTION_DETECTED_OUT_OF_DEPTH_CREATURES);
        manager.add_new_message(detected_creatures);
        manager.send();
      }
    }
  }

  return get_default_skill_action_cost_value(creature);
}

SkillProcessorPtr DetectionSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<DetectionSkillProcessor>();
  return proc;
}
