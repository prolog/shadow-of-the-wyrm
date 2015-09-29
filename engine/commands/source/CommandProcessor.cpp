#include "CommandKeys.hpp"
#include "CommandProcessor.hpp"
#include "Commands.hpp"
#include "CommandCustomValues.hpp"
#include "Conversion.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "RNG.hpp"
#include "TextMessages.hpp"

using namespace std;

CommandProcessor::CommandProcessor()
{
}

CommandProcessor::~CommandProcessor()
{
}

// Determine the type of command, and process it appropriately.
ActionCost CommandProcessor::process(CreaturePtr creature, CommandPtr command, DisplayPtr display)
{  
  ActionCost ac;

  if (command)
  {
    Command* raw_command = command.get();

    DirectionalCommand* d_command = dynamic_cast<DirectionalCommand*>(raw_command);

    if (d_command && !(d_command->get_direction() == Direction::DIRECTION_NULL) /* search is a special case */)
    {
      return process_directional_command(creature, d_command, display);
    } 
    else
    {
      // It's a subclass of the basic command, but not one of the subclasses requiring special processing.
      return process_command(creature, raw_command, display);
    }
  }

  return ac;
}

// Process the Command
ActionCost CommandProcessor::process_command(CreaturePtr creature, Command* command, DisplayPtr display)
{
  ActionCost ac;
  
  if (command)
  {
    bool confirm = process_confirmation(creature, command, display);
    
    if (confirm)
    {
      Game& game = Game::instance();
      string command_name = command->get_name();
      
      if (command_name == CommandKeys::QUIT)
      {
        ac = game.actions.quit(creature);
      }
      else if (command_name == CommandKeys::VERSION)
      {
        ac = game.actions.version(creature);
      }
      else if (command_name == CommandKeys::GAME_DATE_TIME)
      {
        ac = game.actions.date_and_time(creature);
      }
      else if (command_name == CommandKeys::SEARCH)
      {
        ac = game.actions.search(creature);
      }
      else if (command_name == CommandKeys::MOVE_UP)
      {
        ac = game.actions.ascend(creature);
      }
      else if (command_name == CommandKeys::MOVE_DOWN)
      {
        ac = game.actions.descend(creature);
      }
      else if (command_name == CommandKeys::AUTOMATIC_MOVEMENT)
      {
        ac = game.actions.automatic_movement(creature);
      }
      else if (command_name == CommandKeys::PICK_UP_ITEM)
      {
        ac = game.actions.pick_up(creature);
      }
      else if (command_name == CommandKeys::DROP_ITEM)
      {
        ac = game.actions.drop(creature);
      }
      else if (command_name == CommandKeys::CHAR_DUMP)
      {
        ac = game.actions.dump_character(creature);
      }
      else if (command_name == CommandKeys::INVENTORY)
      {
        ac = game.actions.equipment(creature);
      }
      else if (command_name == CommandKeys::PRAY)
      {
        ac = game.actions.pray(creature);
      }
      else if (command_name == CommandKeys::MELEE_WEAPON_INFO)
      {
        ac = game.actions.weapon_info(creature, WeaponStyle::WEAPON_STYLE_MELEE);
      }
      else if (command_name == CommandKeys::RANGED_WEAPON_INFO)
      {
        ac = game.actions.weapon_info(creature, WeaponStyle::WEAPON_STYLE_RANGED);
      }
      else if (command_name == CommandKeys::SELECT_TILE)
      {
        ac = game.actions.select_tile(creature);
      }
      else if (command_name == CommandKeys::FIRE_MISSILE)
      {
        ac = game.actions.fire_missile(creature);
      }
      else if (command_name == CommandKeys::QUAFF)
      {
        ac = game.actions.quaff(creature);
      }
      else if (command_name == CommandKeys::READ)
      {
        ac = game.actions.read(creature);
      }
      else if (command_name == CommandKeys::CHECK_CURRENCY)
      {
        ac = game.actions.check_currency(creature);
      }
      else if (command_name == CommandKeys::SAVE_GAME)
      {
        ac = game.actions.save(creature);
      }
      else if (command_name == CommandKeys::EAT)
      {
        ac = game.actions.eat(creature);
      }
      else if (command_name == CommandKeys::CHAT)
      {
        ac = game.actions.chat(creature);
      }
      else if (command_name == CommandKeys::APPLY_FEATURE)
      {
        ac = game.actions.apply(creature);
      }
      else if (command_name == CommandKeys::QUEST_LIST)
      {
        ac = game.actions.quest_list(creature);
      }
      else if (command_name == CommandKeys::RELOAD_SCRIPTS_AND_SIDS)
      {
        ac = game.actions.reload_scripts_and_sids(creature);
      }
      else if (command_name == CommandKeys::RUN_SCRIPT)
      {
        ac = game.actions.run_script_command(creature);
      }
      else if (command_name == CommandKeys::CAST_SPELL)
      {
        ac = game.actions.cast_spell(creature);
      }
      else if (command_name == CommandKeys::BESTIARY)
      {
        string prompt_for_creature;
        ac = game.actions.bestiary(creature, prompt_for_creature);
      }
      else if (command_name == CommandKeys::EVOKE)
      {
        ac = game.actions.evoke(creature);
      }
      else if (command_name == CommandKeys::SHOW_RESISTANCES)
      {
        ac = game.actions.show_resistances(creature);
      }
      else if (command_name == CommandKeys::SHOW_CONDUCTS)
      {
        ac = game.actions.show_conducts(creature);
      }
      else if (command_name == CommandKeys::LATEST_MESSAGES)
      {
        ac = game.actions.latest_messages(creature);
      }
      else if (command_name == CommandKeys::KICK)
      {
        ac = game.actions.kick(creature);
      }
      else if (command_name == CommandKeys::OFFER)
      {
        ac = game.actions.offer(creature);
      }
      else if (command_name == CommandKeys::SKIN)
      {
        ac = game.actions.skin(creature);
      }
      else if (command_name == CommandKeys::PIETY)
      {
        ac = game.actions.piety(creature);
      }
      else if (command_name == CommandKeys::EXPERIENCE)
      {
        ac = game.actions.experience(creature);
      }
      else if (command_name == CommandKeys::CUSTOM_SCRIPT_COMMAND)
      {
        // All the actions have already been done.
        // Get the custom action cost value, and then use it to
        // update the action coordinator appropriately.
        string custom_acv = command->get_custom_value(CommandCustomValues::COMMAND_CUSTOM_VALUES_ACTION_COST_VALUE);

        if (custom_acv.empty())
        {
          Log::instance().error("Custom script command indicated, but no action cost value provided!");
        }
        else
        {
          ac = game.actions.get_action_cost(creature, String::to_int(custom_acv));
        }
      }
      else if (command_name == CommandKeys::REST)
      {
        game.actions.rest(creature);
      }
    }
  }
  
  return ac;
}

// Process the DirectionalCommand
ActionCost CommandProcessor::process_directional_command(CreaturePtr creature, DirectionalCommand* command, DisplayPtr display)
{
  ActionCost ac;
  
  if (command)
  {
    Game& game = Game::instance();
    string command_name = command->get_name();
    Direction direction = command->get_direction();
    CurrentCreatureAbilities cca;

    if (!cca.can_select_movement_direction(creature, true))
    {
      // If the creature is stunned, intercept the direction before the game
      // even decides whether to move or attack, and change the direction to
      // something random.  There is a 25% chance the creature gets to keep
      // its decided direction.
      if (RNG::percent_chance(75))
      {
        direction = static_cast<Direction>(RNG::range(static_cast<int>(Direction::DIRECTION_SOUTH_WEST), static_cast<int>(Direction::DIRECTION_NORTH_EAST)));
      }
    }

    if (CommandKeys::is_movement_type_key(command_name))
    {
      return game.actions.move(creature, direction);
    }
    else if (CommandKeys::is_attack_type_key(command_name))
    {
      return game.actions.attack(creature, direction);
    }
  }
  
  return ac;
}

// Get a confirmation from the creature's decision strategy, if necessary
bool CommandProcessor::process_confirmation(CreaturePtr creature, Command* command, DisplayPtr display)
{
  bool confirm = true;
  
  if (command && command->requires_confirmation())
  {
    if (creature->get_is_player())
    {
      display->confirm(TextMessages::get_confirmation_message(command->get_confirmation_sid()));
    }
    
    confirm = creature->get_decision_strategy()->get_confirmation();
    
    if (creature->get_is_player())
    {
      display->clear_messages();
    }
  }
  
  return confirm;
}
