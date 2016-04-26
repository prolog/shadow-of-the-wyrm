#include "ActionTextKeys.hpp"
#include "DetectionSkillProcessor.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SkillManager.hpp"

using std::string;

ActionCostValue DetectionSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  
  if (map && map->get_map_type() != MapType::MAP_TYPE_WORLD) // Player's the only creature on the map in this case, so no msgs.
  {
    if (MapUtils::hostile_creature_exists(creature->get_id(), map))
    {
      SkillManager sm;
        
      if (sm.check_skill(creature, SkillType::SKILL_GENERAL_DETECTION))
      {
        string detected_creatures = StringTable::get(ActionTextKeys::ACTION_DETECTED_HOSTILE_CREATURES);
        manager.add_new_message(detected_creatures);
        manager.send();
      }
    }
  }

  return get_default_skill_action_cost_value(creature);
}
