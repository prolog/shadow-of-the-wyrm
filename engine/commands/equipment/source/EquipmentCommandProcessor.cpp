#include "EquipmentCommandKeys.hpp"
#include "EquipmentCommandProcessor.hpp"
#include "EquipmentCommands.hpp"
#include "Game.hpp"

using std::string;

EquipmentCommandProcessor::EquipmentCommandProcessor()
{
}

EquipmentCommandProcessor::~EquipmentCommandProcessor()
{
}

ActionCostValue EquipmentCommandProcessor::process(CreaturePtr creature, CommandPtr command)
{
  ActionCostValue process_result = 1;
  Game* game = Game::instance();
  
  if (game && creature && command)
  {
    Command* raw_command = command.get();
    EquipmentCommand* raw_eq_command = dynamic_cast<EquipmentCommand*>(raw_command);
    
    if (raw_eq_command)
    {
      string command_name = raw_eq_command->get_name();
    
      if (raw_eq_command->is_wear_or_remove_command())
      {
        WearOrRemoveCommand* wear_raw_command = dynamic_cast<WearOrRemoveCommand*>(raw_command);
        
        if (wear_raw_command)
        {
          EquipmentWornLocation worn_slot = wear_raw_command->get_equipment_worn_location();
          
          game->actions.wear_or_remove_item(creature, worn_slot);
        }
      }
      else if (command_name == EquipmentCommandKeys::YOUR_ITEMS)
      {
        game->actions.inventory(creature, creature->get_inventory(), true);
      }
      else if (command_name == EquipmentCommandKeys::EXIT_EQUIPMENT)
      {
        process_result = 0;
      }
    }
  }
      
  return process_result;
}
