#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "DisarmTrapsSkillProcessor.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "Trap.hpp"

using namespace std;

ActionCostValue DisarmTrapsSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

  if (creature && map)
  {
    // Get the tiles around the creature, as well as the tile on which the
    // creature is standing.
    TileDirectionMap direction_tiles = MapUtils::get_adjacent_tiles_to_creature(map, creature);
    direction_tiles[Direction::DIRECTION_NULL] = map->at(map->get_location(creature->get_id()));

    pair<int, TileDirectionMap> num_known_traps = count_known_traps(direction_tiles);

    if (num_known_traps.first > 0)
    {
      bool attempted_disarm = disarm_trap(num_known_traps, creature, map);

      if (attempted_disarm)
      {
        acv = get_default_skill_action_cost_value(creature);
      }
    }
    else
    {
      add_no_nearby_trap_message(creature);
    }
  }

  return acv;
}

pair<int, TileDirectionMap> DisarmTrapsSkillProcessor::count_known_traps(const TileDirectionMap& tdm)
{
  pair<int, TileDirectionMap> num_traps = {0, {}};

  for (const auto& tdm_pair : tdm)
  {
    TilePtr tile = tdm_pair.second;

    TrapPtr trap = dynamic_pointer_cast<Trap>(tile->get_feature());

    if (trap != nullptr && trap->get_is_hidden() == false)
    {
      num_traps.first++;
      num_traps.second[tdm_pair.first] = tdm_pair.second;
    }
  }

  return num_traps;
}

bool DisarmTrapsSkillProcessor::disarm_trap(const std::pair<int, TileDirectionMap>& known_traps, CreaturePtr creature, MapPtr map)
{
  bool attempted_disarm = false;
  Game& game = Game::instance();

  if (creature != nullptr && map != nullptr)
  {
    Direction d = Direction::DIRECTION_NULL;
    TilePtr tile;
    IMessageManager& manager = MessageManagerFactory::instance();

    if (known_traps.first == 1)
    {
      d = known_traps.second.begin()->first;
      tile = known_traps.second.begin()->second;
    }
    else if (known_traps.first > 1)
    {
      game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);
      game.get_display()->redraw();

      // Prompt the player for a particular tile.
      if (creature->get_is_player())
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_GET_DIRECTION));
        manager.send();
      }

      CommandFactoryPtr command_factory = std::make_shared<CommandFactory>();
      KeyboardCommandMapPtr kb_command_map = std::make_shared<KeyboardCommandMap>();
      CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, 0);

      if (base_command)
      {
        std::shared_ptr<DirectionalCommand> dcommand;
        dcommand = std::dynamic_pointer_cast<DirectionalCommand>(base_command);

        if (dcommand)
        {
          Direction selected_dir = dcommand->get_direction();

          if (known_traps.second.find(selected_dir) != known_traps.second.end())
          {
            d = selected_dir;
          }
          else
          {
            manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DISARM_TRAPS_NO_TRAP));
            manager.send();
          }
        }
      }
    }
  }

  return attempted_disarm;
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

