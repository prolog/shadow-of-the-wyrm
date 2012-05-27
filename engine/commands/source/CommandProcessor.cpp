#include <boost/make_shared.hpp>
#include "CommandKeys.hpp"
#include "CommandProcessor.hpp"
#include "Commands.hpp"
#include "Game.hpp"

using namespace std;

CommandProcessor::CommandProcessor()
{
}

CommandProcessor::~CommandProcessor()
{
}

// Determine the type of command, and process it appropriately.
bool CommandProcessor::process(CreaturePtr creature, CommandPtr command, DisplayPtr display)
{  
  if (command)
  {
    Command* raw_command = command.get();

    DirectionalCommand* d_command = dynamic_cast<DirectionalCommand*>(raw_command);

    if (d_command)
    {
      return process_directional_command(creature, d_command, display);
    } 
    else
    {
      // It's a subclass of the basic command, but not one of the subclasses requiring special processing.
      return process_command(creature, raw_command, display);
    }
  }
  
  return false;
}

// Process the Command
bool CommandProcessor::process_command(CreaturePtr creature, Command* command, DisplayPtr display)
{
  bool advance = true;
  
  if (command)
  {
    bool confirm = process_confirmation(creature, command, display);
    
    if (confirm)
    {
      Game* game = Game::instance();
      string command_name = command->get_name();
      
      if (command_name == CommandKeys::QUIT)
      {
        game->quit();
      }
      else if (command_name == CommandKeys::VERSION)
      {
        game->actions.version();
        advance = false;
      }
      else if (command_name == CommandKeys::SEARCH)
      {
        advance = game->actions.search(creature);
      }
      else if (command_name == CommandKeys::MOVE_UP)
      {
        advance = game->actions.ascend(creature);
      }
      else if (command_name == CommandKeys::MOVE_DOWN)
      {
        advance = game->actions.descend(creature);
      }
      else if (command_name == CommandKeys::PICK_UP_ITEM)
      {
        advance = game->actions.pick_up(creature);
      }
      else if (command_name == CommandKeys::DROP_ITEM)
      {
        advance = game->actions.drop(creature);
      }
      else if (command_name == CommandKeys::CHAR_DUMP)
      {
        game->actions.dump_character(creature);
        advance = false;
      }
      else if (command_name == CommandKeys::INVENTORY)
      {
        game->actions.equipment(creature);
      }
    }
  }
  
  return advance;
}

// Process the DirectionalCommand
bool CommandProcessor::process_directional_command(CreaturePtr creature, DirectionalCommand* command, DisplayPtr display)
{
  if (command)
  {
    Game* game = Game::instance();
    string command_name = command->get_name();
    Direction direction = command->get_direction();

    if (CommandKeys::is_movement_type_key(command_name))
    {
      return game->actions.move(creature, direction);
    }
    else if (CommandKeys::is_attack_type_key(command_name))
    {
      return game->actions.attack(creature, direction);
    }
  }
  
  return false;
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
