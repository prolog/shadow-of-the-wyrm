#pragma once
#include "Controller.hpp"
#include "NPCDecisionStrategy.hpp"

class ImmobileDecisionStrategy : public NPCDecisionStrategy
{
  public:
    ImmobileDecisionStrategy(ControllerPtr new_controller);
    
  protected:
    // Functions that are called based on the factory type
    virtual CommandPtr get_decision_for_map(const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, MapPtr view_map);
    virtual CommandPtr get_decision_for_inventory(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands);
    virtual CommandPtr get_decision_for_equipment(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands);

    ControllerPtr controller;
};
