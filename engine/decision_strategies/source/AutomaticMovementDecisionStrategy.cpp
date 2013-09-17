#include <boost/make_shared.hpp>
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
CommandPtr AutomaticMovementDecisionStrategy::get_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, boost::shared_ptr<Map> view_map, int* key_p)
{
  CommandPtr movement_decision = boost::make_shared<AutomaticMovementCommand>();
  return movement_decision;
}

CommandPtr AutomaticMovementDecisionStrategy::get_nonmap_decision(const bool reprompt_on_cmd_not_found, const std::string& this_creature_id, CommandFactoryPtr command_factory, KeyboardCommandMapPtr keyboard_commands, int* key_p)
{
  CommandPtr movement_decision = boost::make_shared<AutomaticMovementCommand>();
  return movement_decision;
}

uint AutomaticMovementDecisionStrategy::get_count(const uint max_count)
{
  return 0;
}

bool AutomaticMovementDecisionStrategy::get_confirmation()
{
  return true;
}

DecisionStrategy* AutomaticMovementDecisionStrategy::copy()
{
  return new AutomaticMovementDecisionStrategy(*this);
}

bool AutomaticMovementDecisionStrategy::serialize(ostream& stream)
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
  return CLASS_ID_AUTOMATIC_MOVEMENT_DECISION_STRATEGY;
}

#ifdef UNIT_TESTS
#include "unit_tests/AutomaticMovementDecisionStrategy_test.cpp"
#endif

