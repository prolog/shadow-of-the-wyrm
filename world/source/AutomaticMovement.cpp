#include "AutomaticMovement.hpp"
#include "Serialize.hpp"

using namespace std;

AutomaticMovement::AutomaticMovement()
: direction(Direction::DIRECTION_NULL), turns(-1), engaged(false)
{
}

AutomaticMovement::AutomaticMovement(const Direction d, const bool engage, const int new_turns)
: direction(d), turns(new_turns), engaged(engage)
{
}

bool AutomaticMovement::operator==(const AutomaticMovement& auto_m) const
{
  bool result = true;

  result = result && (direction == auto_m.direction);
  result = result && (turns == auto_m.turns);
  result = result && (engaged == auto_m.engaged);

  return result;
}

void AutomaticMovement::set_direction(const Direction new_direction)
{
  direction = new_direction;
}

Direction AutomaticMovement::get_direction() const
{
  return direction;
}

void AutomaticMovement::set_turns(const int new_turns)
{
  turns = new_turns;
}

int AutomaticMovement::get_turns() const
{
  return turns;
}

// Set the engaged flag.  If the flag becomes false, also reset the turn
// counter.
void AutomaticMovement::set_engaged(const bool new_engaged)
{
  engaged = new_engaged;

  if (engaged == false)
  {
    turns = -1;
  }
}

bool AutomaticMovement::get_engaged() const
{
  return (engaged &&
          ((turns > 0) || (direction != Direction::DIRECTION_UP && direction != Direction::DIRECTION_DOWN && direction != Direction::DIRECTION_NULL)));
}

bool AutomaticMovement::serialize(ostream& stream) const
{
  Serialize::write_enum(stream, direction);
  Serialize::write_int(stream, turns);
  Serialize::write_bool(stream, engaged);

  return true;
}

bool AutomaticMovement::deserialize(istream& stream)
{
  Serialize::read_enum(stream, direction);
  Serialize::read_int(stream, turns);
  Serialize::read_enum(stream, engaged);

  return true;
}

ClassIdentifier AutomaticMovement::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_AUTOMATIC_MOVEMENT;
}

#ifdef UNIT_TESTS
#include "unit_tests/AutomaticMovement_test.cpp"
#endif

