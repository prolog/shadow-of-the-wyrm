#include "Feature.hpp"

// JCD FIXME NEED COPY CONSTRUCTOR FOR MATERIAL PTR/ TRAP PTR

Feature::Feature(MaterialPtr new_material)
: material(new_material)
{
}

bool Feature::has_trap() const
{
  return (trap);
}

void Feature::set_trap(TrapPtr new_trap)
{
  trap = new_trap;
}

TrapPtr Feature::get_trap()
{
  return trap;
}

bool Feature::can_handle() const
{
  return true;
}

bool Feature::can_kick() const
{
  return true;
}

bool Feature::can_open() const
{
  return false;
}

bool Feature::can_offer() const
{
  return false;
}

bool Feature::can_lock() const
{
  return false;
}

// What happens when we try to offer at the feature?  Usually, dead silence.
bool Feature::offer()
{
  return false;
}

// What happens when we try to open a particular feature?  Usually, absolutely nothing.
bool Feature::open()
{
  return false;
}

void Feature::set_lock(LockPtr new_lock)
{
  if (can_lock())
  {
    lock = new_lock;
  }
}

// Get the lock.  This may be null.
LockPtr Feature::get_lock()
{
  return lock;
}

void Feature::set_material(MaterialPtr new_material)
{
  material = new_material;
}

MaterialPtr Feature::get_material()
{
  return material;
}

// By default, Features are not blocking.
bool Feature::get_is_blocking() const
{
  return false;
}

// Use the material's colour
Colour Feature::get_colour() const
{
  Colour colour = COLOUR_WHITE;
  
  if (material)
  {
    colour = material->get_colour();
  }
  
  return colour;
}
