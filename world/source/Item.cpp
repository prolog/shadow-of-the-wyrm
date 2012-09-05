#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/make_shared.hpp>
#include "Conversion.hpp"
#include "Item.hpp"
#include "NullEffect.hpp"
#include "Wood.hpp"

using std::string;
using boost::make_shared;

Item::Item()
: quantity(1), worn_location(EQUIPMENT_WORN_NONE), status(ITEM_STATUS_UNCURSED), status_identified(false),
artifact(false), type(ITEM_TYPE_MISC), symbol('?'), colour(COLOUR_UNDEFINED), identification_type(ITEM_IDENTIFY_ON_SUCCESSFUL_USE)
{
  // Create a default useful material.  Wood, huh?  Well, I needed something.
  material = make_shared<Wood>();
  effect = make_shared<NullEffect>();
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

void Item::set_quantity(const uint new_quantity)
{
  quantity = new_quantity;
}

uint Item::get_quantity() const
{
  return quantity;
}

bool Item::is_valid_quantity(const uint selected_quantity) const
{
  return ((selected_quantity >= 1) && (selected_quantity <= quantity));
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

bool Item::matches(boost::shared_ptr<Item> i)
{
  bool match = (i);
  
  if (i)
  {
    match &= (usage_description_sid == i->get_usage_description_sid());
    match &= (description_sid       == i->get_description_sid()      );
    match &= (status_identified     == i->get_status_identified()    );
    match &= (weight.get_weight()   == i->get_weight().get_weight()  );
    match &= (worn_location         == i->get_worn_location()        );
    match &= (status                == i->get_status()               );
    match &= (artifact              == i->get_artifact()             );
    match &= (type                  == i->get_type()                 );
    match &= (material->get_type()  == i->get_material()->get_type() );
    
    // Check the concrete implementation class's attributes:
    match &= additional_item_attributes_match(i);
  }
  
  return match;
}

// This function always returns true.  Any type-specific behaviour must
// be implemented in the various Item subclasses.
bool Item::additional_item_attributes_match(boost::shared_ptr<Item> i)
{
  return true;
}

void Item::set_effect(EffectPtr new_effect)
{
  effect = new_effect;
}

EffectPtr Item::get_effect()
{
  return effect;
}

Item* Item::deep_copy()
{
  Item* item = clone();
  
  MaterialPtr new_material = MaterialPtr(material->clone());
  item->set_material(new_material);

  EffectPtr new_effect = EffectPtr(effect->clone());
  item->set_effect(new_effect);
  
  return item;
}

Item* Item::deep_copy_with_new_id()
{
  Item* item = deep_copy();
  
  // Create and set a new item ID.  deep_copy just makes a true copy.
  boost::uuids::uuid new_id = boost::uuids::random_generator()();
  std::string id_s = Uuid::to_string(new_id);
  item->set_id(id_s);
  
  return item;
}
