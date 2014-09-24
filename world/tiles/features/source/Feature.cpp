#include "Feature.hpp"
#include "FeatureFactory.hpp"
#include "MaterialFactory.hpp"
#include "Serialize.hpp"

using namespace std;

// JCD FIXME NEED COPY CONSTRUCTOR FOR TRAP/LOCK PTR WHEN THIS IS COMPLETED

Feature::Feature(const MaterialType new_material)
: material(new_material)
{
}

// Feature itself is very small, so I'm intentionally taking the slightly-
// slower performance instead of having duplicated code.
Feature::Feature(const Feature& feature)
{
  *this = feature;
}

Feature& Feature::operator=(const Feature& feature)
{
  if (this != &feature)
  {
    if (feature.trap)
    {
      trap = std::make_shared<Trap>(*feature.trap);
    }

    if (feature.lock)
    {
      lock = std::make_shared<Lock>(*feature.lock);
    }

    material = feature.material;
  }

  return *this;
}

bool Feature::operator==(const Feature& feature) const
{
  bool result = true;

  result = result && (internal_class_identifier() == feature.internal_class_identifier());

  result = result && (material == feature.material);
  result = result && ((!trap && !(feature.trap)) || (trap && feature.trap && (*trap == *(feature.trap))));
  result = result && ((!lock && !(feature.lock)) || (lock && feature.lock && (*lock == *(feature.lock))));

  return result;
}

pair<string, vector<string>> Feature::get_description_and_replacement_sids() const
{
  string base_description_sid = get_description_sid();
  vector<string> no_replacements;

  return make_pair(base_description_sid, no_replacements);
}

bool Feature::has_trap() const
{
  return (trap != nullptr);
}

void Feature::set_trap(TrapPtr new_trap)
{
  trap = new_trap;
}

TrapPtr Feature::get_trap()
{
  return trap;
}

bool Feature::can_handle(const bool feature_tile_occupied) const
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

string Feature::get_handle_message_sid() const
{
  string empty_sid;
  return empty_sid;
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

void Feature::set_material_type(const MaterialType new_material)
{
  material = new_material;
}

MaterialType Feature::get_material_type() const
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
  
  MaterialPtr materialp = MaterialFactory::create_material(material);
  colour = materialp->get_colour();
  
  return colour;
}

// Most features don't impact piety at all.  Some (like Pews) will.
float Feature::get_piety_loss_multiplier() const
{
  return 1.0f;
}

bool Feature::serialize(ostream& stream) const
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

  Serialize::write_enum(stream, material);

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

  Serialize::read_enum(stream, material);

  return true;
}

ClassIdentifier Feature::internal_class_identifier() const
{
  return CLASS_ID_FEATURE;
}
