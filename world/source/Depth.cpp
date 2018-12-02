#include "Conversion.hpp"
#include "Depth.hpp"
#include "Serialize.hpp"

using namespace std;

// Depth 1 is -50 feet (under ground, positive depth).
// Depth -1 is 50 feet (above ground, negative depth).
int Depth::DEPTH_MULTIPLIER = -50;

Depth::Depth()
: current(0), minimum(0), maximum(0), increment(1), has_max(true)
{
}

Depth::Depth(const int cur, const int min, const int max, const int incr, const bool has_maxi)
: current(cur), minimum(min), maximum(max), increment(incr), has_max(has_maxi)
{
}

bool Depth::operator==(const Depth& d) const
{
  bool result = true;

  result = result && (current == d.current);
  result = result && (minimum == d.minimum);
  result = result && (maximum == d.maximum);
  result = result && (increment == d.increment);
  result = result && (has_max == d.has_max);

  return result;
}

void Depth::set_current(const int new_current)
{
  current = new_current;
}

int Depth::get_current() const
{
  return current;
}

void Depth::set_minimum(const int new_minimum)
{
  minimum = new_minimum;
}

int Depth::get_minimum() const
{
  return minimum;
}

void Depth::set_maximum(const int new_maximum)
{
  maximum = new_maximum;
}

int Depth::get_maximum() const
{
  return maximum;
}

void Depth::set_has_maximum(const bool new_has_maximum)
{
  has_max = new_has_maximum;
}

bool Depth::has_maximum() const
{
  return has_max;
}

void Depth::set_increment(const int new_increment)
{
  increment = new_increment;
}

int Depth::get_increment() const
{
  return increment;
}

// Return the "next" depth.
Depth Depth::lower() const
{
  Depth d(current, minimum, maximum, increment, has_max);

  if (has_maximum() == false || (current < maximum))
  {
    if (current < numeric_limits<int>::max())
    {
      d.set_current(current + std::abs(increment));
    }
  }

  return d;
}

// Return the "previous" depth.
Depth Depth::higher() const
{
  Depth d(current, minimum, maximum, increment, has_max);

  if (has_maximum() == false || (current > minimum))
  {
    if (current > numeric_limits<int>::min())
    {
      d.set_current(current - std::abs(increment));
    }
  }

  return d;
}

bool Depth::has_more_levels(const Direction d) const
{
  bool more_levels = false;

  if (!has_max)
  {
    more_levels = true;
  }
  else
  {
    if (d == Direction::DIRECTION_DOWN)
    {
      more_levels = ((current + std::abs(increment)) <= maximum);
    }
    else if (d == Direction::DIRECTION_UP)
    {
      more_levels = ((current - std::abs(increment)) >= minimum);
    }
  }

  return more_levels;
}

// Return the depth as a string (for the UI, etc): e.g., "[-50']", "" (if on overworld, or otherwise at 0')
string Depth::str() const
{
  string depth_s; // Default, if on plains, forest, etc.

  if (current != 0)
  {
    int depth_in_feet = current * DEPTH_MULTIPLIER;
    depth_s = std::to_string(depth_in_feet);
    depth_s = "[" + depth_s + "']";
  }
  
  return depth_s;
}

bool Depth::serialize(ostream& stream) const
{
  Serialize::write_int(stream, current);
  Serialize::write_int(stream, minimum);
  Serialize::write_int(stream, maximum);
  Serialize::write_int(stream, increment);
  Serialize::write_bool(stream, has_max);
  Serialize::write_int(stream, DEPTH_MULTIPLIER);

  return true;
}

bool Depth::deserialize(istream& stream)
{
  Serialize::read_int(stream, current);
  Serialize::read_int(stream, minimum);
  Serialize::read_int(stream, maximum);
  Serialize::read_int(stream, increment);
  Serialize::read_bool(stream, has_max);
  Serialize::read_int(stream, DEPTH_MULTIPLIER);

  return true;
}

ClassIdentifier Depth::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_DEPTH;
}

#ifdef UNIT_TESTS
#include "unit_tests/Depth_test.cpp"
#endif

