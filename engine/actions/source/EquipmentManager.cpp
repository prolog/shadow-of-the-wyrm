#include "EquipmentCommandFactory.hpp"
#include "EquipmentCommandProcessor.hpp"
#include "EquipmentKeyboardCommandMap.hpp"
#include "EquipmentManager.hpp"
#include "EquipmentTranslator.hpp"

EquipmentManager::EquipmentManager(DisplayPtr new_display, CreaturePtr new_creature)
: display(new_display), creature(new_creature)
{
}

EquipmentManager::~EquipmentManager()
{
}

// Do the actual equipment management, interfacing with the UI as needed.
ActionCostValue EquipmentManager::manage_equipment()
{
  ActionCostValue total_action_cost = 0;
  ActionCostValue action_cost = 0; // Looking at eq has no cost - adding or removing items will update this.
  
  bool manage_eq = true; // For looping

  if (creature)
  {
    CommandFactoryPtr command_factory    = CommandFactoryPtr(new EquipmentCommandFactory());
    KeyboardCommandMapPtr kb_command_map = KeyboardCommandMapPtr(new EquipmentKeyboardCommandMap());
    
    while (manage_eq)
    {
      if (display && creature->get_is_player())
      {
        DisplayEquipmentMap dem = EquipmentTranslator::create_display_equipment(creature);
        display->display_equipment(dem);
      }
      
      DecisionStrategyPtr decision_strategy = creature->get_decision_strategy();
      
      if (decision_strategy)
      {
        CommandPtr equipment_command = decision_strategy->get_decision(creature->get_id(), command_factory, kb_command_map);
        action_cost = EquipmentCommandProcessor::process(creature, equipment_command);
        
        if ((action_cost > 0) && (total_action_cost == 0))
        {
          total_action_cost = action_cost;
        }
      }
      else
      {
        manage_eq = 0;
      }
      
      // -1 is a special value for the equipment command.  "0" means "don't advance the turn,
      // but keep the equipment screen up."  "-1" means "exit was selected."
      if (action_cost == -1)
      {
        manage_eq = 0;
      }
    }
    
    if (display && creature->get_is_player()) // Clean up the menu
    {
      display->clear_menu();
    }
  }

  return total_action_cost;
}

ActionCostValue EquipmentManager::get_action_cost_value() const
{
  // JCD FIXME
  return 1;
}
