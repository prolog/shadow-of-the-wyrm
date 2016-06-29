#include "ActionTextKeys.hpp"
#include "DisarmTrapsSkillProcessor.hpp"
#include "MessageManagerFactory.hpp"
#include "Trap.hpp"

using namespace std;

ActionCostValue DisarmTrapsSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

  if (creature && map)
  {
    TileDirectionMap direction_tiles = MapUtils::get_adjacent_tiles_to_creature(map, creature);

    if (has_known_trap(direction_tiles))
    {
      acv = get_default_skill_action_cost_value(creature);
    }
    else
    {
      add_no_nearby_trap_message(creature);
    }
  }

  return acv;
}

bool DisarmTrapsSkillProcessor::has_known_trap(const TileDirectionMap& tdm)
{
  for (const auto& tdm_pair : tdm)
  {
    TilePtr tile = tdm_pair.second;

    TrapPtr trap = dynamic_pointer_cast<Trap>(tile->get_feature());

    if (trap != nullptr && trap->get_is_hidden() == false)
    {
      return true;
    }
  }

  return false;
}

void DisarmTrapsSkillProcessor::add_no_nearby_trap_message(CreaturePtr creature)
{
  if (creature != nullptr && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DISARM_TRAPS_NO_TRAPS));
    manager.send();
  }
}

// Disarming traps takes a while.
ActionCostValue DisarmTrapsSkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return 30;
}

