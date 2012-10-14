#include "Feature.hpp"
#include "FeatureFactory.hpp"
#include "MaterialFactory.hpp"
#include "Serialize.hpp"

using namespace std;

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

bool Feature::serialize(ostream& stream)
{
  if (trap)
  {
    Serialize::write_class_id(stream, trap->get_class_identifier());
    trap->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, CLASS_ID_NULL);
  }

  if (lock)
  {
    Serialize::write_class_id(stream, lock->get_class_identifier());
    lock->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, CLASS_ID_NULL);
  }

  if (material)
  {
    Serialize::write_class_id(stream, material->get_class_identifier());
    material->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, CLASS_ID_NULL);
  }

  return true;
}

bool Feature::deserialize(istream& stream)
{
  ClassIdentifier trap_clid;
  Serialize::read_class_id(stream, trap_clid);

  if (trap_clid != CLASS_ID_NULL)
  {
    trap = FeatureFactory::create_trap();
    trap->deserialize(stream);
  }

  ClassIdentifier lock_clid;
  Serialize::read_class_id(stream, lock_clid);

  if (lock_clid != CLASS_ID_NULL)
  {
    lock = FeatureFactory::create_lock();
    lock->deserialize(stream);
  }

  ClassIdentifier material_clid;
  Serialize::read_class_id(stream, material_clid);

  if (material_clid != CLASS_ID_NULL)
  {
    material = MaterialFactory::create_material(material_clid);
    if (!material) return false;
    if (!material->deserialize(stream)) return false;
  }

  return true;
}

ClassIdentifier Feature::internal_class_identifier() const
{
  return CLASS_ID_FEATURE;
}
