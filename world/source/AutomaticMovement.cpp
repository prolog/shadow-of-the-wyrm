#include "AutomaticMovement.hpp"
#include "Serialize.hpp"

using namespace std;

AutomaticMovement::AutomaticMovement()
: direction(Direction::DIRECTION_NULL), engaged(false)
{
}

AutomaticMovement::AutomaticMovement(const Direction d, const bool engage)
: direction(d), engaged(engage)
{
}

bool AutomaticMovement::operator==(const AutomaticMovement& auto_m) const
{
  bool result = true;

  result = result && (direction == auto_m.direction);
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

void AutomaticMovement::set_engaged(const bool new_engaged)
{
  engaged = new_engaged;
}

bool AutomaticMovement::get_engaged() const
{
  return (engaged &&
          direction != Direction::DIRECTION_NULL &&
          direction != Direction::DIRECTION_UP &&
          direction != Direction::DIRECTION_DOWN);
}

bool AutomaticMovement::serialize(ostream& stream) const
{
  Serialize::write_enum(stream, direction);
  Serialize::write_bool(stream, engaged);

  return true;
}

bool AutomaticMovement::deserialize(istream& stream)
{
  Serialize::read_enum(stream, direction);
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

