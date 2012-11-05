#include "Conversion.hpp"
#include "Depth.hpp"
#include "Serialize.hpp"

using namespace std;

// Depth 1 is -50 feet (under ground, positive depth).
// Depth -1 is 50 feet (above ground, negative depth).
int Depth::DEPTH_MULTIPLIER = -50;

Depth::Depth()
: current(0), maximum(0)
{
}

Depth::Depth(const int cur, const int max)
: current(cur), maximum(max)
{
}

void Depth::set_current(const int new_current)
{
  current = new_current;
}

int Depth::get_current() const
{
  return current;
}

void Depth::set_maximum(const int new_maximum)
{
  maximum = new_maximum;
}

int Depth::get_maximum() const
{
  return maximum;
}

// Return the depth as a string (for the UI, etc): e.g., "[-50']", "" (if on overworld, or otherwise at 0')
string Depth::str() const
{
  string depth_s; // Default, if on plains, forest, etc.

  if (current != 0)
  {
    int depth_in_feet = current * DEPTH_MULTIPLIER;
    depth_s = Integer::to_string(depth_in_feet);
    depth_s = "[" + depth_s + "']";
  }
  
  return depth_s;
}

bool Depth::serialize(ostream& stream)
{
  Serialize::write_int(stream, current);
  Serialize::write_int(stream, maximum);
  Serialize::write_int(stream, DEPTH_MULTIPLIER);

  return true;
}

bool Depth::deserialize(istream& stream)
{
  Serialize::read_int(stream, current);
  Serialize::read_int(stream, maximum);
  Serialize::read_int(stream, DEPTH_MULTIPLIER);

  return true;
}

ClassIdentifier Depth::internal_class_identifier() const
{
  return CLASS_ID_DEPTH;
}

#ifdef UNIT_TESTS
#include "unit_tests/Depth_test.cpp"
#endif

