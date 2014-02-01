#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include "Conversion.hpp"
#include "global_prototypes.hpp"
#include "Item.hpp"
#include "NullEffect.hpp"
#include "MaterialFactory.hpp"
#include "RNG.hpp"
#include "Wood.hpp"

#include "EffectFactory.hpp"
#include "MaterialFactory.hpp"
#include "Serialize.hpp"

using namespace std;

namespace ItemEnchanting
{
  // Minimum/maximum number of enchantments on an item.
  const int MIN_ENCHANTS = 6;
  const int MAX_ENCHANTS = 9;

  // Minimum/maximum number of points per enchant.
  const int MIN_POINTS = 3;
  const int MAX_POINTS = 6;
};

Item::Item()
: quantity(1), readable(false), worn_location(EQUIPMENT_WORN_NONE), status(ITEM_STATUS_UNCURSED), status_identified(false), 
item_identified(false), artifact(false), type(ITEM_TYPE_MISC), symbol('?'), colour(COLOUR_UNDEFINED), 
identification_type(ITEM_IDENTIFY_ON_SUCCESSFUL_USE), effect(EFFECT_TYPE_NULL), material(MATERIAL_TYPE_WOOD),
glowing(false)
{
  resistances.set_all_resistances_to(0);
  initialize_remaining_enchants();
}

Item::~Item()
{
}

bool Item::operator==(const Item& i) const
{
  bool result = true;

  result = result && (id == i.id);
  result = result && (base_id == i.base_id);
  result = result && (quantity == i.quantity);
  result = result && (usage_description_sid == i.usage_description_sid);
  result = result && (unidentified_usage_description_sid == i.unidentified_usage_description_sid);
  result = result && (description_sid == i.description_sid);
  result = result && (unidentified_description_sid == i.unidentified_description_sid);
  result = result && (weight == i.weight);
  result = result && (readable == i.readable);
  result = result && (worn_location == i.worn_location);
  result = result && (status == i.status);
  result = result && (item_identified == i.item_identified);
  result = result && (status_identified == i.status_identified);
  result = result && (artifact == i.artifact);
  result = result && (type == i.type);
  result = result && (symbol == i.symbol);
  result = result && (colour == i.colour);
  result = result && (identification_type == i.identification_type);
  result = result && (effect == i.effect);
  result = result && (material == i.material);
  result = result && (glowing == i.glowing);
  result = result && (resistances == i.resistances);
  result = result && (remaining_enchants == i.remaining_enchants);

  return result;
}

void Item::set_id(const std::string& new_id)
{
  id = new_id;
}

std::string Item::get_id() const
{
  return id;
}

void Item::set_base_id(const std::string& new_base_id)
{
  base_id = new_base_id;
}

string Item::get_base_id() const
{
  return base_id;
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

string Item::get_synopsis() const
{
  string empty_synopsis;
  return empty_synopsis;
}

void Item::set_readable(const bool new_readable)
{
  readable = new_readable;
}

bool Item::get_readable() const
{
  return readable;
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

void Item::set_material_type(const MaterialType new_material)
{
  material = new_material;
}

MaterialType Item::get_material_type() const
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
    if (colour == COLOUR_UNDEFINED)
    {
      MaterialPtr materialp = MaterialFactory::create_material(material);
      return materialp->get_colour();
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

bool Item::matches(std::shared_ptr<Item> i)
{
  bool match = (i != nullptr);

  if (match)
  {
    match = match && (usage_description_sid == i->get_usage_description_sid());
    match = match && (description_sid       == i->get_description_sid()      );
    match = match && (status_identified     == i->get_status_identified()    );
    match = match && (weight.get_weight()   == i->get_weight().get_weight()  );
    match = match && (worn_location         == i->get_worn_location()        );
    match = match && (status                == i->get_status()               );
    match = match && (artifact              == i->get_artifact()             );
    match = match && (type                  == i->get_type()                 );
    match = match && (material              == i->get_material_type()        );
    match = match && (effect                == i->get_effect_type()          );
    match = match && (glowing               == i->get_glowing()              );
    match = match && (resistances           == i->get_resistances()          );
    // Don't consider the remaining enchantments for purposes of matching...

    // Check the concrete implementation class's attributes:
    match = match && additional_item_attributes_match(i);
  }
  
  return match;
}

// This function always returns true.  Any type-specific behaviour must
// be implemented in the various Item subclasses.
bool Item::additional_item_attributes_match(std::shared_ptr<Item> i)
{
  return true;
}

void Item::set_effect_type(const EffectType new_effect)
{
  effect = new_effect;
}

EffectType Item::get_effect_type() const
{
  return effect;
}

void Item::set_glowing(const bool new_glowing)
{
  glowing = new_glowing;
}

bool Item::get_glowing() const
{
  return glowing;
}

void Item::set_resistances(const Resistances& new_resistances)
{
  resistances = new_resistances;
}

Resistances Item::get_resistances() const
{
  return resistances;
}

Resistances& Item::get_resistances_ref()
{
  return resistances;
}

Item* Item::create_with_new_id()
{
  Item* item = create();
  
  // Create and set a new item ID.  deep_copy just makes a true copy.
  boost::uuids::uuid new_id = boost::uuids::random_generator()();
  std::string id_s = Uuid::to_string(new_id);
  item->set_id(id_s);
  
  return item;
}

// By default, create and clone are the same.  For items that have properties
// that need to be reset on clone (wands' charges, for example), these functions
// will be different to allow for that behaviour.
Item* Item::create()
{
  return clone();
}

void Item::set_item_identified(const bool new_item_identified)
{
  item_identified = new_item_identified;
}

bool Item::get_item_identified() const
{
  bool identified = item_identified;

  if (!identified)
  {
    identified = (unidentified_description_sid == description_sid);
  }

  return identified;
}

void Item::initialize_remaining_enchants()
{
  Statistic new_rem(RNG::range(ItemEnchanting::MIN_ENCHANTS, ItemEnchanting::MAX_ENCHANTS));
  set_remaining_enchants(new_rem);
}

bool Item::can_enchant() const
{
  bool can_enchant = !get_artifact();

  if (can_enchant)
  {
    can_enchant = (remaining_enchants.get_current() > 0);
  }

  return can_enchant;
}

bool Item::enchant(const float enchant_mult)
{
  bool enchanted = true;
  
  if (can_enchant())
  {
    int points = static_cast<int>(RNG::range(ItemEnchanting::MIN_POINTS, ItemEnchanting::MAX_POINTS) * enchant_mult);
    do_enchant_item(points);

    enchanted = true;
  }

  return enchanted;
}

void Item::set_remaining_enchants(const Statistic& new_remaining_enchants)
{
  remaining_enchants = new_remaining_enchants;
}

Statistic Item::get_remaining_enchants() const
{
  return remaining_enchants;
}

void Item::do_enchant_item(const int points)
{
  // Enchant between 1 and 3 resistances.
  uint num_resists = RNG::range(1, 3);

  vector<DamageType> resvul_dt_vec;
  vector<DamageType> unused_dt_vec;

  // Get a list of resistances/vulns.
  // For items, these are values != 0.
  // Also track the non-zero ones, so that if there are additional "slots"
  // to enchant, one can be selected.
  for (DamageType dt = DAMAGE_TYPE_FIRST; dt < DAMAGE_TYPE_MAX; dt++)
  {
    if (!dequal(resistances.get_resistance_value(dt), 0))
    {
      resvul_dt_vec.push_back(dt);
    }
    else
    {
      unused_dt_vec.push_back(dt);
    }
  }

  // Randomly shuffle the already-resisted and yet-to-be-resisted damage
  // types to determine what will be resisted.
  random_shuffle(resvul_dt_vec.begin(), resvul_dt_vec.end(), RNG::get_generator());
  random_shuffle(unused_dt_vec.begin(), unused_dt_vec.end(), RNG::get_generator());

  // The enchantment amount is the number of points divided by the number of
  // enchantments, int-and-then-float-ified.
  int base_enchant_amt = points / num_resists;
  float enchant_amt = base_enchant_amt / 100.0f;

  // Start with the initial damage types and enchant a number of them.
  uint i = 0;
  for (; i < num_resists; i++)
  {
    if (i >= resvul_dt_vec.size())
    {
      break;
    }

    DamageType dt = resvul_dt_vec.at(i);
    resistances.set_resistance_value(dt, resistances.get_resistance_value(dt) + enchant_amt);
  }

  // Any carryover is applied to the unused damage types.
  uint j = 0;
  for (; i < num_resists; i++)
  {
    if (j >= unused_dt_vec.size())
    {
      break;
    }

    DamageType dt = unused_dt_vec.at(j);
    resistances.set_resistance_value(dt, resistances.get_resistance_value(dt) + enchant_amt);

    j++;
  }
}

bool Item::serialize(ostream& stream) const
{
  Serialize::write_string(stream, id);
  Serialize::write_string(stream, base_id);
  Serialize::write_uint(stream, quantity);
  Serialize::write_string(stream, usage_description_sid);
  Serialize::write_string(stream, description_sid);
  Serialize::write_string(stream, unidentified_usage_description_sid);
  Serialize::write_string(stream, unidentified_description_sid);

  weight.serialize(stream);

  Serialize::write_bool(stream, readable);
  Serialize::write_enum(stream, worn_location);
  Serialize::write_enum(stream, status);
  Serialize::write_bool(stream, status_identified);
  Serialize::write_bool(stream, item_identified);
  Serialize::write_bool(stream, artifact);
  Serialize::write_enum(stream, type);
  Serialize::write_uchar(stream, symbol);
  Serialize::write_enum(stream, colour);
  Serialize::write_enum(stream, identification_type);
  Serialize::write_enum(stream, effect);
  Serialize::write_enum(stream, material);
  Serialize::write_bool(stream, glowing);

  resistances.serialize(stream);
  remaining_enchants.serialize(stream);

  return true;
}

bool Item::deserialize(istream& stream)
{
  Serialize::read_string(stream, id);
  Serialize::read_string(stream, base_id);
  Serialize::read_uint(stream, quantity);
  Serialize::read_string(stream, usage_description_sid);
  Serialize::read_string(stream, description_sid);
  Serialize::read_string(stream, unidentified_usage_description_sid);
  Serialize::read_string(stream, unidentified_description_sid);

  weight.deserialize(stream);

  Serialize::read_bool(stream, readable);
  Serialize::read_enum(stream, worn_location);
  Serialize::read_enum(stream, status);
  Serialize::read_bool(stream, status_identified);
  Serialize::read_bool(stream, item_identified);
  Serialize::read_bool(stream, artifact);
  Serialize::read_enum(stream, type);
  Serialize::read_uchar(stream, symbol);
  Serialize::read_enum(stream, colour);
  Serialize::read_enum(stream, identification_type);
  Serialize::read_enum(stream, effect);
  Serialize::read_enum(stream, material);
  Serialize::read_bool(stream, glowing);

  resistances.deserialize(stream);
  remaining_enchants.deserialize(stream);

  return true;
}
