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
  ActionCostValue action_cost = 0;
  
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
      }
      else
      {
        manage_eq = 0;
      }
      
      if (action_cost == 0)
      {
        manage_eq = 0;
      }
    }
    
    if (display && creature->get_is_player()) // Clean up the menu
    {
      display->clear_menu();
    }
    
    action_cost = get_action_cost_value();
  }

  return action_cost;
}

ActionCostValue EquipmentManager::get_action_cost_value() const
{
  // JCD FIXME
  return 1;
}
