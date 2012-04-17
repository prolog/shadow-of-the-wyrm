#include <boost/make_shared.hpp>
#include "Item.hpp"
#include "Wood.hpp"

using std::string;
using boost::make_shared;

Item::Item()
: worn_location(EQUIPMENT_WORN_NONE), status(ITEM_STATUS_UNCURSED), status_identified(false),
artifact(false), type(ITEM_TYPE_MISC), symbol('?'), colour(COLOUR_UNDEFINED), identification_type(ITEM_IDENTIFY_ON_SUCCESSFUL_USE)
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

void Item::set_usage_description_sid(const string& new_usage_description_sid)
{
  usage_description_sid = new_usage_description_sid;
}

string Item::get_usage_description_sid() const
{
  return usage_description_sid;
}

void Item::set_description_sid(const string& new_description_sid)
{
  description_sid = new_description_sid;
}

string Item::get_description_sid() const
{
  return description_sid;
}

void Item::set_unidentified_usage_description_sid(const std::string& new_unident_usage_description_sid)
{
  unidentified_usage_description_sid = new_unident_usage_description_sid;
}

string Item::get_unidentified_usage_description_sid() const
{
  return unidentified_usage_description_sid;
}

void Item::set_unidentified_description_sid(const std::string& new_unident_description_sid)
{
  unidentified_description_sid = new_unident_description_sid;
}

string Item::get_unidentified_description_sid() const
{
  return unidentified_description_sid;
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

void Item::set_status_identified(const bool new_status_identified)
{
  status_identified = new_status_identified;
}

bool Item::get_status_identified() const
{
  return status_identified;
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

void Item::set_symbol(const uchar new_symbol)
{
  symbol = new_symbol;
}

uchar Item::get_symbol() const
{
  return symbol;
}

void Item::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour Item::get_colour() const
{
  if (artifact)
  {
    return COLOUR_BOLD_CYAN;
  }
  else
  {
    // If the colour has been overridden
    if ((colour == COLOUR_UNDEFINED) && material)
    {
      return material->get_colour();
    }
    else if (colour != COLOUR_UNDEFINED)
    {
      return colour;
    }
  }

  // If none of the previous rules match, return a bold white colour.  This should serve as an indication in the UI
  // that something is amiss (maybe!).
  return COLOUR_BOLD_WHITE;
}

void Item::set_identification_type(const ItemIdentificationType new_identification_type)
{
  identification_type = new_identification_type;
}

ItemIdentificationType Item::get_identification_type() const
{
  return identification_type;
}

void Item::set_identified(const bool new_identified)
{
  identified = new_identified;
}

bool Item::get_identified() const
{
  return identified;
}

Item* Item::deep_copy()
{
  Item* item = clone();
  
  material = MaterialPtr(material->clone());
  item->set_material(material);
  
  return item;
}
