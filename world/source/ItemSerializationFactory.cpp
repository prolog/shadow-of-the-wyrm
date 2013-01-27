#include <boost/make_shared.hpp>
#include "ItemSerializationFactory.hpp"
#include "Ammunition.hpp"
#include "Amulet.hpp"
#include "Armour.hpp"
#include "Boat.hpp"
#include "Book.hpp"
#include "Currency.hpp"
#include "Food.hpp"
#include "MiscItem.hpp"
#include "Plant.hpp"
#include "Potion.hpp"
#include "Ring.hpp"
#include "Scroll.hpp"
#include "SerializationExceptions.hpp"
#include "Staff.hpp"
#include "Tool.hpp"
#include "Wand.hpp"
#include "Weapon.hpp"

using namespace std;

ItemSerializationMap ItemSerializationFactory::item_map;

ItemSerializationFactory::ItemSerializationFactory()
{
}

ItemSerializationFactory::~ItemSerializationFactory()
{
}

ItemPtr ItemSerializationFactory::create_item(const ClassIdentifier ci)
{
  ItemPtr item;

  if (item_map.empty())
  {
    initialize_item_map();
  }

  ItemSerializationMap::iterator i_it = item_map.find(ci);

  if (i_it != item_map.end())
  {
    item = ItemPtr(i_it->second->clone());
  }

  // Sanity check: throw an exception if the item is null!
  if (!item)
  {
    throw SerializationException("Couldn't re-create an item - missing type in map?");
  }

  return item;
}

void ItemSerializationFactory::initialize_item_map()
{
  item_map.clear();

  ItemPtr ammo   = boost::make_shared<Ammunition>();
  ItemPtr amulet = boost::make_shared<Amulet>();
  ItemPtr armour = boost::make_shared<Armour>();
  ItemPtr boat   = boost::make_shared<Boat>();
  ItemPtr book   = boost::make_shared<Book>();
  ItemPtr cash   = boost::make_shared<Currency>();
  ItemPtr food   = boost::make_shared<Food>();
  ItemPtr misc   = boost::make_shared<MiscItem>();
  ItemPtr plant  = boost::make_shared<Plant>();
  ItemPtr potion = boost::make_shared<Potion>();
  ItemPtr ring   = boost::make_shared<Ring>();
  ItemPtr scroll = boost::make_shared<Scroll>();
  ItemPtr staff  = boost::make_shared<Staff>();
  ItemPtr wand   = boost::make_shared<Wand>();
  ItemPtr melee  = boost::make_shared<MeleeWeapon>();
  ItemPtr ranged = boost::make_shared<RangedWeapon>();
  ItemPtr tool   = boost::make_shared<Tool>();

  item_map.insert(make_pair(CLASS_ID_AMMUNITION, ammo));
  item_map.insert(make_pair(CLASS_ID_AMULET, amulet));
  item_map.insert(make_pair(CLASS_ID_ARMOUR, armour));
  item_map.insert(make_pair(CLASS_ID_BOAT, boat));
  item_map.insert(make_pair(CLASS_ID_BOOK, book));
  item_map.insert(make_pair(CLASS_ID_CURRENCY, cash));
  item_map.insert(make_pair(CLASS_ID_FOOD, food));
  item_map.insert(make_pair(CLASS_ID_MISC_ITEM, misc));
  item_map.insert(make_pair(CLASS_ID_PLANT, plant));
  item_map.insert(make_pair(CLASS_ID_POTION, potion));
  item_map.insert(make_pair(CLASS_ID_RING, ring));
  item_map.insert(make_pair(CLASS_ID_SCROLL, scroll));
  item_map.insert(make_pair(CLASS_ID_STAFF, staff));
  item_map.insert(make_pair(CLASS_ID_WAND, wand));
  item_map.insert(make_pair(CLASS_ID_MELEE_WEAPON, melee));
  item_map.insert(make_pair(CLASS_ID_RANGED_WEAPON, ranged));
  item_map.insert(make_pair(CLASS_ID_TOOL, tool));
}

