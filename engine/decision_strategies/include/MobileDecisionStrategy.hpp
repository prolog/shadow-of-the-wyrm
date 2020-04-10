#pragma once
#include "Controller.hpp"
#include "NPCDecisionStrategy.hpp"

class MobileDecisionStrategy : public NPCDecisionStrategy
{
  public:
    MobileDecisionStrategy(ControllerPtr new_controller);

    DecisionStrategy* copy() override;
        
  protected:
    // Functions that are called based on the factory type
    virtual CommandPtr get_decision_for_inventory(CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands) override;
    virtual CommandPtr get_decision_for_equipment(CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands) override;
    virtual CommandPtr get_decision_for_tile_selection(CommandFactory* command_factory, KeyboardCommandMap* keyboard_commands) override;
    
  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
