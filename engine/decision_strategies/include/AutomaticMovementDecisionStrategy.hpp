#pragma once
#include "AutomaticMovement.hpp"
#include "DecisionStrategy.hpp"

// A decision strategy class that uses an AutomaticMovement object to
// generate the appropriate Command object.
//
// Since this class only really generates movement commands, the other
// functions that it is required to implement (confirmation, count, etc.)
// will all return default-type values.
class AutomaticMovementDecisionStrategy : public DecisionStrategy
{
  public:
    AutomaticMovementDecisionStrategy(const AutomaticMovement& movement, ControllerPtr new_controller);
    virtual ~AutomaticMovementDecisionStrategy() {};

    virtual bool operator==(const AutomaticMovementDecisionStrategy& ds) const;

    virtual CommandPtr get_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, std::shared_ptr<Map> view_map = std::shared_ptr<Map>() /* optional - only used when getting a decision on the main map, and only for non-player characters. */, int* key_p = 0);
    virtual CommandPtr get_nonmap_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, int* key_p = 0);

    virtual uint get_count(const uint max_count);
    virtual bool get_confirmation();

    virtual DecisionStrategy* copy() ;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    AutomaticMovement move;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

