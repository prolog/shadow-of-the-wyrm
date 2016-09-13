#include "ThieverySkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

ThieverySkillProcessor::ThieverySkillProcessor()
{
}

ActionCostValue ThieverySkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = 0;

  if (creature && map)
  {
    acv = get_default_skill_action_cost_value(creature);

    bool adj_creatures = check_for_adjacent_creatures(creature, map);

    if (adj_creatures)
    {
      // ...
    }
  }

  return acv;
}

// Check to see if there are any creature, hostile or not, that are adjacent
// to the given creature.
bool ThieverySkillProcessor::check_for_adjacent_creatures(CreaturePtr creature, MapPtr map)
{
  bool adj_creatures = false;

  if (creature != nullptr && map != nullptr)
  {
    TileDirectionMap tdm = MapUtils::get_adjacent_tiles_to_creature(map, creature);

    for (const auto& tile_pair : tdm)
    {
      TilePtr tile = tile_pair.second;

      if (tile != nullptr && tile->has_creature())
      {
        adj_creatures = true;
        break;
      }
    }
  }

  if (!adj_creatures && creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_THIEVERY_NO_TARGETS));
    manager.send();
  }

  return adj_creatures;
}

ActionCostValue ThieverySkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return 20;
}
