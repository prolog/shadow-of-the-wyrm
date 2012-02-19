#include "InventoryCommandFactory.hpp"
#include "InventoryCommandProcessor.hpp"
#include "InventoryKeyboardCommandMap.hpp"
#include "InventoryManager.hpp"
#include "InventoryTranslator.hpp"

InventoryManager::InventoryManager(DisplayPtr new_display, CreaturePtr new_creature)
: display(new_display), creature(new_creature)
{
}

InventoryManager::~InventoryManager()
{
}

ItemPtr InventoryManager::manage_inventory()
{
  ItemPtr selected_item;
  bool manage_inv = true;

  if (creature)
  {
    CommandFactoryPtr command_factory    = CommandFactoryPtr(new InventoryCommandFactory());
    KeyboardCommandMapPtr kb_command_map = KeyboardCommandMapPtr(new InventoryKeyboardCommandMap());
    
    while (manage_inv)
    {
      if (display && creature->get_is_player())
      {
        DisplayInventoryMap display_inventory = InventoryTranslator::create_display_inventory(creature);
        display->display_inventory(display_inventory);
      }

      DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
      
      if (decision_strategy)
      {
        CommandPtr inventory_command = decision_strategy->get_decision(command_factory, kb_command_map);
        manage_inv = InventoryCommandProcessor::process(creature, inventory_command, selected_item);
      }
      else
      {
        manage_inv = false;
      }
    }
    
    if (creature->get_is_player())
    {
      display->clear_menu();
    } 
  }
  
  return selected_item;
}
