#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "CoordUtils.hpp"
#include "DisarmTrapsSkillProcessor.hpp"
#include "Features.hpp"
#include "Game.hpp"
#include "ItemManager.hpp"
#include "ItemProperties.hpp"
#include "IFeatureManipulatorFactory.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "StatisticsMarker.hpp"

using namespace std;

DisarmTrapsSkillProcessor::DisarmTrapsSkillProcessor()
{
  disarm_traps_outcome_functions[DisarmTrapsOutcome::DISARM_TRAPS_DISARM] = &DisarmTrapsSkillProcessor::disarm_trap_success;
  disarm_traps_outcome_functions[DisarmTrapsOutcome::DISARM_TRAPS_DISMANTLE] = &DisarmTrapsSkillProcessor::disarm_trap_dismantle;
  disarm_traps_outcome_functions[DisarmTrapsOutcome::DISARM_TRAPS_FAIL] = &DisarmTrapsSkillProcessor::disarm_trap_fail;
  disarm_traps_outcome_functions[DisarmTrapsOutcome::DISARM_TRAPS_TRIGGER] = &DisarmTrapsSkillProcessor::disarm_trap_trigger;
}

ActionCostValue DisarmTrapsSkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = ActionCostConstants::NO_ACTION_MENU;

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

SkillProcessorPtr DisarmTrapsSkillProcessor::clone()
{
  SkillProcessorPtr proc = std::make_unique<DisarmTrapsSkillProcessor>();
  return proc;
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
  IMessageManager& manager = MMF::instance();

  if (creature == nullptr || creature->get_is_player() == false)
  {
    manager = MMF::instance(MessageTransmit::SELF, nullptr, false);
  }

  if (creature != nullptr && map != nullptr)
  {
    Direction d = Direction::DIRECTION_NULL;
    TilePtr tile;

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

      CommandFactoryPtr command_factory = std::make_unique<CommandFactory>();
      KeyboardCommandMapPtr kb_command_map = std::make_unique<KeyboardCommandMap>();
      CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory.get(), kb_command_map.get(), 0, true);

      if (base_command != nullptr)
      {
        DirectionalCommand* dcommand;
        dcommand = dynamic_cast<DirectionalCommand*>(base_command.get());

        if (dcommand)
        {
          Direction selected_dir = dcommand->get_direction();
          auto kt_it = known_traps.second.find(selected_dir);
          if (kt_it != known_traps.second.end())
          {
            d = selected_dir;
            tile = kt_it->second;
          }
          else
          {
            manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DISARM_TRAPS_NO_TRAP));
            manager.send();

            return false;
          }
        }
      }
    }

    if (tile != nullptr)
    {
      TrapPtr trap = dynamic_pointer_cast<Trap>(tile->get_feature());

      DisarmTrapsCalculator dtc;
      DisarmTrapsOutcome dto = dtc.calculate_disarm_traps_outcome(creature, trap && trap->has_items());

      // Process the outcome.
      auto d_it = disarm_traps_outcome_functions.find(dto);

      if (d_it != disarm_traps_outcome_functions.end())
      {
        (this->*(d_it->second))(creature, map, d, tile, manager);
        attempted_disarm = true;
      }
    }
  }

  return attempted_disarm;
}

void DisarmTrapsSkillProcessor::add_no_nearby_trap_message(CreaturePtr creature)
{
  if (creature != nullptr && creature->get_is_player())
  {
    IMessageManager& manager = MMF::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DISARM_TRAPS_NO_TRAPS));
    manager.send();
  }
}

// Disarming traps takes a while.
ActionCostValue DisarmTrapsSkillProcessor::get_default_skill_action_cost_value(CreaturePtr /*creature*/) const
{
  return 30;
}

void DisarmTrapsSkillProcessor::disarm_trap_success(CreaturePtr creature, MapPtr map, const Direction /*d*/, TilePtr tile, IMessageManager& manager)
{
  if (creature != nullptr && map != nullptr)
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DISARM_TRAPS_OUTCOME_DISARM));
    manager.send();

    if (tile != nullptr)
    {
      tile->remove_feature();
    }

    creature->get_skills().mark(SkillType::SKILL_GENERAL_DISARM_TRAPS);
  }
}

void DisarmTrapsSkillProcessor::disarm_trap_dismantle(CreaturePtr creature, MapPtr map, const Direction /*d*/, TilePtr tile, IMessageManager& manager)
{
  if (creature != nullptr && map != nullptr)
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DISARM_TRAPS_OUTCOME_DISMANTLE));
    manager.send();

    // Remove the trap, and add any components to the tile.
    if (tile != nullptr)
    {
      TrapPtr trap = dynamic_pointer_cast<Trap>(tile->get_feature());
      tile->remove_feature();

      if (trap != nullptr)
      {
        string item_id = trap->get_item_id();

        if (!item_id.empty())
        {
          ItemManager im;
          uint quantity = static_cast<uint>(trap->get_uses());

          if (quantity > 0)
          {
            im.create_item_with_probability(100, 100, tile->get_items(), item_id, quantity);
          }
        }
      }
    }

    // Successfully and usefully dismantling a trap marks Dexterity
    // and Disarm Traps itself.
    StatisticsMarker sm;
    sm.mark_dexterity(creature);
    creature->get_skills().mark(SkillType::SKILL_GENERAL_DISARM_TRAPS);
  }
}

void DisarmTrapsSkillProcessor::disarm_trap_fail(CreaturePtr creature, MapPtr map, const Direction /*d*/, TilePtr /*tile*/, IMessageManager& manager)
{
  if (creature != nullptr && map != nullptr)
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DISARM_TRAPS_OUTCOME_FAIL));
    manager.send();

    creature->get_skills().mark(SkillType::SKILL_GENERAL_DISARM_TRAPS);
  }
}

void DisarmTrapsSkillProcessor::disarm_trap_trigger(CreaturePtr creature, MapPtr map, const Direction d, TilePtr tile, IMessageManager& manager)
{
  if (creature != nullptr && map != nullptr)
  {
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DISARM_TRAPS_OUTCOME_TRIGGER));
    manager.send();

    // If the tile doesn't have a creature on it, move on to the tile.
    if (tile != nullptr && tile->has_creature() == false)
    {
      Coordinate creature_coords = map->get_location(creature->get_id());
      TilePtr creature_current_tile = map->at(creature_coords);
      MapUtils::add_or_update_location(map, creature, CoordUtils::get_new_coordinate(creature_coords, d), creature_current_tile);

      FeatureManipulatorPtr trap_manip = IFeatureManipulatorFactory::create_manipulator(tile->get_feature());

      if (trap_manip != nullptr)
      {
        trap_manip->handle(tile, creature);
      }
    }
  }
}
