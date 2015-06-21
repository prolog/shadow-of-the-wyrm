#include "Creature.hpp"
#include "Feature.hpp"
#include "FeatureFactory.hpp"
#include "MaterialFactory.hpp"
#include "Serialize.hpp"

using namespace std;

// JCD FIXME NEED COPY CONSTRUCTOR FOR LOCK PTR WHEN THIS IS COMPLETED

Feature::Feature(const MaterialType new_material, const AlignmentRange new_alignment_range, const int new_uses)
: material(new_material), alignment_range(new_alignment_range), uses(new_uses)
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
    if (feature.lock)
    {
      lock = std::make_shared<Lock>(*feature.lock);
    }

    material = feature.material;
    alignment_range = feature.alignment_range;
    uses = feature.uses;
  }

  return *this;
}

bool Feature::operator==(const Feature& feature) const
{
  bool result = true;

  result = result && (internal_class_identifier() == feature.internal_class_identifier());

  result = result && (material == feature.material);
  result = result && ((!lock && !(feature.lock)) || (lock && feature.lock && (*lock == *(feature.lock))));
  result = result && (alignment_range == feature.alignment_range);
  result = result && (uses == feature.uses);

  return result;
}

// At the moment, only traps are hidden - everything else is visible.
bool Feature::get_is_hidden() const
{
  return false;
}

bool Feature::apply_on_movement(std::shared_ptr<Creature> creature) const
{
  return false;
}

pair<string, vector<string>> Feature::get_description_and_replacement_sids() const
{
  string base_description_sid = get_description_sid();
  vector<string> no_replacements;

  return make_pair(base_description_sid, no_replacements);
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
  Colour colour = Colour::COLOUR_WHITE;
  
  MaterialPtr materialp = MaterialFactory::create_material(material);
  colour = materialp->get_colour();
  
  return colour;
}

// Most features don't impact piety at all.  Some (like Pews) will.
float Feature::get_piety_loss_multiplier() const
{
  return 1.0f;
}

void Feature::set_alignment_range(const AlignmentRange new_alignment_range)
{
  alignment_range = new_alignment_range;
}

AlignmentRange Feature::get_alignment_range() const
{
  return AlignmentRange::ALIGNMENT_RANGE_NEUTRAL;
}

void Feature::set_uses(const int new_uses)
{
  uses = new_uses;
}

int Feature::get_uses() const
{
  return uses;
}

float Feature::get_hp_regeneration_multiplier() const
{
  return 1.0f;
}

float Feature::get_ap_regeneration_multiplier() const
{
  return 1.0f;
}

bool Feature::serialize(ostream& stream) const
{
  if (lock)
  {
    Serialize::write_class_id(stream, lock->get_class_identifier());
    lock->serialize(stream);
  }
  else
  {
    Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
  }

  Serialize::write_enum(stream, material);
  Serialize::write_enum(stream, alignment_range);
  Serialize::write_enum(stream, uses);

  return true;
}

bool Feature::deserialize(istream& stream)
{
  ClassIdentifier lock_clid;
  Serialize::read_class_id(stream, lock_clid);

  if (lock_clid != ClassIdentifier::CLASS_ID_NULL)
  {
    lock = FeatureFactory::create_lock();
    lock->deserialize(stream);
  }

  Serialize::read_enum(stream, material);
  Serialize::read_enum(stream, alignment_range);
  Serialize::read_int(stream, uses);

  return true;
}

ClassIdentifier Feature::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_FEATURE;
}
