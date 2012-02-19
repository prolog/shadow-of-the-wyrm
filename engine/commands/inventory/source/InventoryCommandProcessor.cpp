#include "Game.hpp"
#include "InventoryCommandKeys.hpp"
#include "InventoryCommandProcessor.hpp"

using std::string;

InventoryCommandProcessor::InventoryCommandProcessor()
{
}

InventoryCommandProcessor::~InventoryCommandProcessor()
{
}

bool InventoryCommandProcessor::process(CreaturePtr creature, CommandPtr command, ItemPtr selected_item)
{
  bool process_result = true;

  Game* game = Game::instance();

  if (game && creature && command)
  {
    string command_name = command->get_name();
    
    if (command_name == InventoryCommandKeys::EXIT_INVENTORY)
    {
      process_result = false;
    }
    else if (command_name == InventoryCommandKeys::CLEAR_FILTER)
    {
      // FIXME
    }
    else if (command_name == InventoryCommandKeys::FILTER_VIEW)
    {
      // FIXME
    }
    else if (command_name == InventoryCommandKeys::NEXT_PAGE)
    {
      // FIXME
    }
    else if (command_name == InventoryCommandKeys::PREVIOUS_PAGE)
    {
      // FIXME
    }
    else if (command_name == InventoryCommandKeys::SELECT_ITEM)
    {
      // FIXME
      // selected_item = ...;
    }
  }

  return process_result;
}
