#include "Conversion.hpp"
#include "Depth.hpp"

using std::string;

const int Depth::DEPTH_MULTIPLIER = 50;

Depth::Depth()
: current(0), maximum(0)
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
