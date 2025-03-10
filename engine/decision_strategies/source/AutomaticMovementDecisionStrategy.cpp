#include "Commands.hpp"
#include "AutomaticMovementDecisionStrategy.hpp"
#include "Serialize.hpp"

using namespace std;

AutomaticMovementDecisionStrategy::AutomaticMovementDecisionStrategy(const AutomaticMovement& movement, ControllerPtr new_controller)
: DecisionStrategy(new_controller), move(movement)
{
}

bool AutomaticMovementDecisionStrategy::operator==(const AutomaticMovementDecisionStrategy& ds) const
{
  bool result = DecisionStrategy::operator==(ds);

  result = result && (move == ds.move);

  return result;
}

// Translate the automatic movement details into an actual command ptr.
CommandPtr AutomaticMovementDecisionStrategy::get_decision(const bool /*reprompt_on_cmd_not_found*/, const std::string& /*this_creature_id*/, CommandFactory* /*command_factory*/, KeyboardCommandMap* /*keyboard_commands*/, std::shared_ptr<Map> /*view_map*/, int* /*key_p*/)
{
  CommandPtr movement_decision = std::make_unique<AutomaticMovementCommand>(-1);
  return movement_decision;
}

CommandPtr AutomaticMovementDecisionStrategy::get_nonmap_decision(const bool /*reprompt_on_cmd_not_found*/, const std::string& /*this_creature_id*/, CommandFactory* /*command_factory*/, KeyboardCommandMap* /*keyboard_commands*/, int* /*key_p*/, const bool /*refresh_window*/)
{
  CommandPtr movement_decision = std::make_unique<AutomaticMovementCommand>(-1);
  return movement_decision;
}

uint AutomaticMovementDecisionStrategy::get_count(const uint /*max_count*/)
{
  return 0;
}

bool AutomaticMovementDecisionStrategy::get_confirmation(const bool /*confirmation_default_value*/, const bool /*require_proper_selection*/)
{
  return true;
}

bool AutomaticMovementDecisionStrategy::get_attack_confirmation(CreaturePtr creature)
{
  return (creature != nullptr);
}

DecisionStrategy* AutomaticMovementDecisionStrategy::copy()
{
  return new AutomaticMovementDecisionStrategy(*this);
}

bool AutomaticMovementDecisionStrategy::serialize(ostream& stream) const
{
  DecisionStrategy::serialize(stream);
  move.serialize(stream);

  return true;
}

bool AutomaticMovementDecisionStrategy::deserialize(istream& stream)
{
  DecisionStrategy::deserialize(stream);
  move.deserialize(stream);

  return true;
}

ClassIdentifier AutomaticMovementDecisionStrategy::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_AUTOMATIC_MOVEMENT_DECISION_STRATEGY;
}

#ifdef UNIT_TESTS
#include "unit_tests/AutomaticMovementDecisionStrategy_test.cpp"
#endif

