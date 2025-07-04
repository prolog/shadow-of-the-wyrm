#include "Equipment.hpp"
#include "ItemProperties.hpp"
#include "ItemSerializationFactory.hpp"
#include "Serialize.hpp"

using namespace std;

Equipment::Equipment()
{
  initialize();
}

Equipment::~Equipment()
{
}

bool Equipment::operator==(const Equipment& e) const
{
  bool result = true;

  for (int i = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); i < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); i++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(i);

    ItemPtr item_a = get_item(ewl);
    ItemPtr item_b = e.get_item(ewl);

    // To be equivalent, the slots either both need to be empty, or both
    // contain an item and have the items match.
    result = result && ((!item_a && !item_b) || ((item_a && item_b) && (*item_a == *item_b)));

    if (!result) break;
  }

  return result;
}

// Set an item, but only if it's not null.  There are no checks done here to
// see if the slot is correct - that's a higher-level check.
bool Equipment::set_item(ItemPtr item, const EquipmentWornLocation worn_location)
{
  bool item_set = false;
  
  if (item)
  {
    equipment[worn_location] = item;
    item_set = true;
  }
  
  return item_set;
}

bool Equipment::has_item(const EquipmentWornLocation worn_location) const
{
  bool iexists = false;
  auto e_it = equipment.find(worn_location);

  if (e_it != equipment.end() && e_it->second != nullptr)
  {
    iexists = true;
  }

  return iexists;
}

// Get the item being worn in a certain slot.
ItemPtr Equipment::get_item(const EquipmentWornLocation worn_location) const
{
  ItemPtr current_item;
  EquipmentMap::const_iterator c_it = equipment.find(worn_location);
  
  if (c_it != equipment.end())
  {
    current_item = c_it->second;
  }

  return current_item;
}

pair<bool, ItemPtr> Equipment::has_item_with_property(const std::string& property)
{
  pair <bool, ItemPtr> item_details = { false, nullptr };

  for (int i = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); i < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); i++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(i);
    ItemPtr item = get_item(ewl);

    if (item != nullptr && item->has_additional_property(property))
    {
      item_details = { true, item };
      break;
    }
  }

  return item_details;
}

// Get the item with a particular id
ItemPtr Equipment::get_item_from_id(const string& id) const
{
  ItemPtr i;

  for (auto c_it : equipment)
  {
    ItemPtr c_item = c_it.second;

    if (c_item != nullptr && c_item->get_id() == id)
    {
      i = c_item;
      break;
    }
  }

  return i;
}

// Remove an item from a particular slot, and return it.
ItemPtr Equipment::remove_item(const EquipmentWornLocation worn_location)
{
  ItemPtr previously_worn_item;
  ItemPtr no_item;

  auto e_it = equipment.find(worn_location);

  if (e_it != equipment.end())
  {
    previously_worn_item = e_it->second;
    equipment[worn_location] = no_item;
  }
  
  return previously_worn_item;
}

// Count the number of items, but exclude currency, which does not count
// towards the max number.
uint Equipment::count_items() const
{
  uint count = 0;

  for (int e = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); e < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); e++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(e);
    ItemPtr item = get_item(ewl);

    if (item != nullptr && (item->get_type() != ItemType::ITEM_TYPE_CURRENCY))
    {
      count += item->get_quantity();
    }
  }

  return count;
}

bool Equipment::is_digging_implement_equipped() const
{
  bool is_digger = false;
  ItemPtr item = get_item(EquipmentWornLocation::EQUIPMENT_WORN_WIELDED);

  if (item != nullptr)
  {
    is_digger = !item->get_additional_property(ItemProperties::ITEM_PROPERTIES_DIG_HARDNESS).empty();
  }

  return is_digger;
}

// Initialize the internal map of items.
void Equipment::initialize()
{
  equipment.clear();

  for (int i = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); i < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); i++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(i);
    ItemPtr no_item;
    equipment[ewl] = no_item;
  }
}

// Check to see if a heap of items can be equipped
bool Equipment::can_equip_multiple_items(const EquipmentWornLocation ewl) const
{
  return (ewl == EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION);
}

bool Equipment::merge(ItemPtr item)
{
  for (int i = static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_HEAD); i < static_cast<int>(EquipmentWornLocation::EQUIPMENT_WORN_LAST); i++)
  {
    EquipmentWornLocation ewl = static_cast<EquipmentWornLocation>(i);

    ItemPtr slot_item = get_item(ewl);
    
    if (slot_item && ewl == EquipmentWornLocation::EQUIPMENT_WORN_AMMUNITION && slot_item->matches(item))
    {
      slot_item->set_quantity(slot_item->get_quantity() + item->get_quantity());
      
      return true;
    }
  }
  
  return false;
}

// Get the current set of equipment.
EquipmentMap Equipment::get_equipment() const
{
  return equipment;
}

bool Equipment::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, equipment.size());

  for (const EquipmentMap::value_type& eq_pair : equipment)
  {
    Serialize::write_enum(stream, eq_pair.first);

    ItemPtr item = eq_pair.second;

    if (item)
    {
      Serialize::write_class_id(stream, item->get_class_identifier());
      item->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
    }
  }

  return true;
}

bool Equipment::deserialize(istream& stream)
{
  size_t equipment_size = 0;
  Serialize::read_size_t(stream, equipment_size);

  // Don't clear the equipment - by default it will have all empty slots, which we
  // want.  Use operator[] instead of insert() to ensure that the values are updated.
  for (unsigned int i = 0; i < equipment_size; i++)
  {
    EquipmentWornLocation ewl = EquipmentWornLocation::EQUIPMENT_WORN_HEAD;
    ItemPtr item;
    Serialize::read_enum(stream, ewl);

    ClassIdentifier eq_clid = ClassIdentifier::CLASS_ID_NULL;
    Serialize::read_class_id(stream, eq_clid);

    if (eq_clid != ClassIdentifier::CLASS_ID_NULL)
    {
      item = ItemSerializationFactory::create_item(eq_clid);
      if (!item) return false;
      if (!item->deserialize(stream)) return false;
    }

    // Always insert, even if the shared pointer to the item is "null" -
    // this just means that nothing is equipped at that slot.
    equipment[ewl] = item;
  }

  return true;
}

ClassIdentifier Equipment::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_EQUIPMENT;
}

#ifdef UNIT_TESTS
#include "unit_tests/Equipment_test.cpp"
#endif

