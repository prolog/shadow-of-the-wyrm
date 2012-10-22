#include <boost/foreach.hpp>
#include "Equipment.hpp"
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

// Remove an item from a particular slot, and return it.
ItemPtr Equipment::remove_item(const EquipmentWornLocation worn_location)
{
  ItemPtr previously_worn_item = equipment[worn_location];
  ItemPtr no_item;
  
  if (previously_worn_item)
  {
    equipment[worn_location] = no_item;
  }
  
  return previously_worn_item;
}

// Initialize the internal map of items.
void Equipment::initialize()
{
  equipment.clear();
  
  for (EquipmentWornLocation worn_location = EQUIPMENT_WORN_HEAD; worn_location < EQUIPMENT_WORN_LAST; worn_location++)
  {
    ItemPtr no_item;
    equipment[worn_location] = no_item;
  }
}

// Check to see if a heap of items can be equipped
bool Equipment::can_equip_multiple_items(const EquipmentWornLocation ewl) const
{
  return (ewl == EQUIPMENT_WORN_AMMUNITION);
}

bool Equipment::merge(ItemPtr item)
{
  for (EquipmentWornLocation ewl = EQUIPMENT_WORN_HEAD; ewl < EQUIPMENT_WORN_LAST; ewl++)
  {
    ItemPtr slot_item = get_item(ewl);
    
    if (slot_item && slot_item->matches(item))
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

bool Equipment::serialize(ostream& stream)
{
  Serialize::write_size_t(stream, equipment.size());

  BOOST_FOREACH(EquipmentMap::value_type& eq_pair, equipment)
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
      Serialize::write_class_id(stream, CLASS_ID_NULL);
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
    EquipmentWornLocation ewl = EQUIPMENT_WORN_HEAD;
    ItemPtr item;
    Serialize::read_enum(stream, ewl);

    ClassIdentifier eq_clid = CLASS_ID_NULL;
    Serialize::read_class_id(stream, eq_clid);

    if (eq_clid != CLASS_ID_NULL)
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
  return CLASS_ID_EQUIPMENT;
}