#include "ActionTextKeys.hpp"
#include "Detection.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SkillManager.hpp"

using std::string;

void Detection::detect_creatures_if_necessary(CreaturePtr creature, MapPtr map, const string& original_map_id, const string& current_map_id)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  
  if (original_map_id != current_map_id) // We've just loaded a new map
  {
    if (map && map->get_map_type() != MAP_TYPE_WORLD) // Player's the only creature on the map in this case, so no msgs.
    {
      if (MapUtils::hostile_creature_exists(creature->get_id(), map))
      {
        SkillManager sm;
        
        if (sm.check_skill(creature, SKILL_GENERAL_DETECTION))
        {
          string detected_creatures = StringTable::get(ActionTextKeys::ACTION_DETECTED_HOSTILE_CREATURES);
          manager.add_new_message(detected_creatures);
          manager.send();
        }
      }
    }
  }
}
