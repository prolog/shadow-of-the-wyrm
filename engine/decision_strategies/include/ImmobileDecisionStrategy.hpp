#pragma once
#include "Controller.hpp"
#include "NPCDecisionStrategy.hpp"

class ImmobileDecisionStrategy : public NPCDecisionStrategy
{
  public:
    ImmobileDecisionStrategy(ControllerPtr new_controller);

    DecisionStrategy* copy();
        
  protected:
    // Functions that are called based on the factory type
    virtual CommandPtr get_decision_for_inventory(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands);
    virtual CommandPtr get_decision_for_equipment(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands);
    virtual CommandPtr get_decision_for_tile_selection(CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands);
    
    virtual bool can_move() const;

    ControllerPtr controller;
};
