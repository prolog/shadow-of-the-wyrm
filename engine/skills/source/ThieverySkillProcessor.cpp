#include "ThieverySkillProcessor.hpp"
#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "CommandFactory.hpp"
#include "Conversion.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureProperties.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "KeyboardCommandMap.hpp"
#include "MapUtils.hpp"
#include "RaceManager.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"

using namespace std;

ThieverySkillProcessor::ThieverySkillProcessor()
{
}

ActionCostValue ThieverySkillProcessor::process(CreaturePtr creature, MapPtr map)
{
  ActionCostValue acv = -1;

  if (creature && map)
  {
    // Redraw the main map so any prompts don't look odd.
    Game& game = Game::instance();
    game.update_display(creature, game.get_current_map(), creature->get_decision_strategy()->get_fov_map(), false);

    pair<bool, TileDirectionMap> adj_creatures_pair = check_for_adjacent_creatures(creature, map);
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature->get_is_player());

    if (adj_creatures_pair.first && !adj_creatures_pair.second.empty())
    {
      TileDirectionMap tdm = adj_creatures_pair.second;
      size_t tdm_sz = tdm.size();
      Direction d;
      CreaturePtr steal_creature;
      TilePtr steal_tile;

      if (tdm_sz == 1)
      {
        d = tdm.begin()->first;
        steal_tile = tdm.begin()->second;

        if (steal_tile)
        {
          steal_creature = steal_tile->get_creature();
        }
      }
      else
      {
        CommandFactoryPtr command_factory = std::make_shared<CommandFactory>();
        KeyboardCommandMapPtr kb_command_map = std::make_shared<KeyboardCommandMap>();

        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_GET_DIRECTION));
        manager.send();

        CommandPtr base_command = creature->get_decision_strategy()->get_nonmap_decision(false, creature->get_id(), command_factory, kb_command_map, 0);

        if (base_command)
        {
          // Check to see if it's an actual directional command
          std::shared_ptr<DirectionalCommand> dcommand;
          dcommand = std::dynamic_pointer_cast<DirectionalCommand>(base_command);

          if (dcommand)
          {
            TilePtr tile = MapUtils::get_adjacent_tile(map, creature, dcommand->get_direction());

            if (tile && tile->has_creature())
            {
              steal_creature = tile->get_creature();
            }
          }
        }
      }

      if (steal_creature != nullptr)
      {
        acv = process_steal(creature, steal_creature, manager);
      }
    }
  }

  return acv;
}

// Check to see if there are any creature, hostile or not, that are adjacent
// to the given creature.
pair<bool, TileDirectionMap> ThieverySkillProcessor::check_for_adjacent_creatures(CreaturePtr creature, MapPtr map)
{
  pair<bool, TileDirectionMap> result;
  TileDirectionMap tdm;

  if (creature != nullptr && map != nullptr)
  {
    tdm = MapUtils::get_adjacent_tiles_to_creature(map, creature);

    for (const auto& tile_pair : tdm)
    {
      TilePtr tile = tile_pair.second;

      if (tile != nullptr && tile->has_creature())
      {
        result.first = true;
        result.second.insert(tile_pair);
      }
    }
  }

  if (!result.first && creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_THIEVERY_NO_TARGETS));
    manager.send();
  }

  return result;
}

// Process the steal: first check to see if the creature we're trying to steal
// from is the stealing creature, and if not, to the necessary checks to see
// if the thievery was successful.
ActionCostValue ThieverySkillProcessor::process_steal(CreaturePtr stealing_creature, CreaturePtr steal_creature, IMessageManager& manager)
{
  ActionCostValue acv = -1;

  // Used for only sending messages the player should see.
  IMessageManager& pl_manager = MessageManagerFactory::instance(stealing_creature, stealing_creature && stealing_creature->get_is_player());

  if (stealing_creature != nullptr && steal_creature != nullptr)
  {
    if (stealing_creature->get_id() == steal_creature->get_id())
    {
      pl_manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_THIEVERY_SELF_TARGET));
      pl_manager.send();
    }
    else
    {
      CreatureDescriber cd(stealing_creature, steal_creature, true);
      
      if (already_stolen_from(steal_creature))
      {
        pl_manager.add_new_message(ActionTextKeys::get_already_stolen_message(cd.describe()));
        pl_manager.send();
      }
      else
      {
        // Can we steal from this creature?  E.g., insects don't have pockets.
        RaceManager rm;
        RacePtr steal_race = rm.get_race(steal_creature->get_race_id());

        if (steal_race && steal_race->get_has_pockets())
        {
          bool steal = false;

          // Stealing from hostile creatures is always okay...
          if (steal_creature->get_decision_strategy()->get_threats_ref().has_threat(stealing_creature->get_id()).first)
          {
            steal = true;
          }
          // ...it's the innocents that some of the deities have issues with.
          else
          {
            manager.add_new_confirmation_message(TextMessages::get_confirmation_message(TextKeys::DECISION_STEAL_FRIENDLY_CREATURE));
            steal = stealing_creature->get_decision_strategy()->get_confirmation();

            if (steal)
            {
              // Attacking and stealing are considered one and the same by the Nine.
              Game::instance().get_deity_action_manager_ref().notify_action(stealing_creature, CreatureActionKeys::ACTION_ATTACK_FRIENDLY);
            }
          }

          if (steal)
          {
            HostilityManager hm;
            hm.set_hostility_to_creature(steal_creature, stealing_creature->get_id());
            steal_creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_STOLEN_FROM, to_string(true));

            acv = get_default_skill_action_cost_value(stealing_creature);
          }
        }
        else
        {
          pl_manager.add_new_message(ActionTextKeys::get_no_pockets_message(cd.describe()));
          pl_manager.send();
        }
      }
    }
  }

  return acv;
}

// Has the targetted creature already been pilfered?
bool ThieverySkillProcessor::already_stolen_from(CreaturePtr creature)
{
  bool stolen = false;

  if (creature != nullptr && !creature->get_is_player())
  {
    stolen = String::to_bool(creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_STOLEN_FROM));
  }

  return stolen;
}

ActionCostValue ThieverySkillProcessor::get_default_skill_action_cost_value(CreaturePtr creature) const
{
  return 20;
}
