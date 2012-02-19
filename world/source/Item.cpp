#include <boost/make_shared.hpp>
#include "Item.hpp"
#include "Wood.hpp"

using std::string;
using boost::make_shared;

Item::Item()
: worn_location(EQUIPMENT_WORN_NONE), artifact(false), type(ITEM_TYPE_MISC)
{
  // Create a default useful material.  Wood, huh?  Well, I needed something.
  material = make_shared<Wood>();
}

Item::~Item()
{
}

void Item::set_id(const std::string& new_id)
{
  id = new_id;
}

std::string Item::get_id() const
{
  return id;
}

void Item::set_description_sid(const string& new_description_sid)
{
  description_sid = new_description_sid;
}

string Item::get_description_sid() const
{
  return description_sid;
}

void Item::set_weight(const Weight& new_weight)
{
  weight = new_weight;
}

Weight Item::get_weight() const
{
  return weight;
}

void Item::set_worn_location(const EquipmentWornLocation new_worn_location)
{
  worn_location = new_worn_location;
}

EquipmentWornLocation Item::get_worn_location() const
{
  return worn_location;
}

void Item::set_status(const ItemStatus new_status)
{
  status = new_status;
}

ItemStatus Item::get_status() const
{
  return status;
}

void Item::set_artifact(const bool new_artifact)
{
  artifact = new_artifact;
}

bool Item::get_artifact() const
{
  return artifact;
}

void Item::set_type(const ItemType new_type)
{
  type = new_type;
}

ItemType Item::get_type() const
{
  return type;
}

void Item::set_material(MaterialPtr new_material)
{
  material = new_material;
}

MaterialPtr Item::get_material() const
{
  return material;
}
