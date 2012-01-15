#include "Item.hpp"

using std::string;

Item::Item()
: worn_location(EQUIPMENT_WORN_NONE)
{
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
