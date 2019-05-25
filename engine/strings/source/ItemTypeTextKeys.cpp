#include "ItemTypeTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

// Item types
ItemTypeTextKeys::ItemTypeTextKeys()
{
}

ItemTypeTextKeys::~ItemTypeTextKeys()
{
}

string ItemTypeTextKeys::get_item_type_description_singular(const ItemType itype)
{
  static_assert(ItemType::ITEM_TYPE_LAST == ItemType(16), "Unexpected ITEM_TYPE_LAST");

  string desc_sid;

  switch (itype)
  {
    case ItemType::ITEM_TYPE_AMMUNITION:
      desc_sid = ITEM_TYPE_AMMUNITION_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_AMULET:
      desc_sid = ITEM_TYPE_AMULET_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_ARMOUR:
      desc_sid = ITEM_TYPE_ARMOUR_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_BOAT:
      desc_sid = ITEM_TYPE_BOAT_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_CURRENCY:
      desc_sid = ITEM_TYPE_CURRENCY_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_FOOD:
      desc_sid = ITEM_TYPE_FOOD_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_LAST:
      break;
    case ItemType::ITEM_TYPE_MISC:
      desc_sid = ITEM_TYPE_MISC_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_NULL:
      break;
    case ItemType::ITEM_TYPE_PLANT:
      desc_sid = ITEM_TYPE_PLANT_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_POTION:
      desc_sid = ITEM_TYPE_POTION_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_RING:
      desc_sid = ITEM_TYPE_RING_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_SCROLL:
      desc_sid = ITEM_TYPE_SCROLL_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_SPELLBOOK:
      desc_sid = ITEM_TYPE_BOOK_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_STAFF:
      desc_sid = ITEM_TYPE_STAFF_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_TOOL:
      desc_sid = ITEM_TYPE_TOOL_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_WAND:
      desc_sid = ITEM_TYPE_WAND_SINGULAR;
      break;
    case ItemType::ITEM_TYPE_WEAPON:
      desc_sid = ITEM_TYPE_WEAPON_SINGULAR;
      break;
  }

  return StringTable::get(desc_sid);
}

string ItemTypeTextKeys::get_food_type(const FoodType ft)
{
  string desc_sid;

  switch (ft)
  {
    case FoodType::FOOD_TYPE_VEGETABLE:
      desc_sid = ItemTypeTextKeys::FOOD_TYPE_VEGETABLE;
      break;
    case FoodType::FOOD_TYPE_MEAT:
      desc_sid = ItemTypeTextKeys::FOOD_TYPE_MEAT;
      break;
    case FoodType::FOOD_TYPE_CARBS:
      desc_sid = ItemTypeTextKeys::FOOD_TYPE_CARBS;
      break;
    case FoodType::FOOD_TYPE_DAIRY:
      desc_sid = ItemTypeTextKeys::FOOD_TYPE_DAIRY;
      break;
    case FoodType::FOOD_TYPE_OTHER:
      desc_sid = ItemTypeTextKeys::FOOD_TYPE_OTHER;
      break;
  }

  return StringTable::get(desc_sid);
}

// public
const string ItemTypeTextKeys::ITEM_TYPE_MISC       = "ITEM_TYPE_MISC";
const string ItemTypeTextKeys::ITEM_TYPE_WEAPONS    = "ITEM_TYPE_WEAPONS";
const string ItemTypeTextKeys::ITEM_TYPE_ARMOURS    = "ITEM_TYPE_ARMOURS";
const string ItemTypeTextKeys::ITEM_TYPE_POTIONS    = "ITEM_TYPE_POTIONS";
const string ItemTypeTextKeys::ITEM_TYPE_BOOKS      = "ITEM_TYPE_BOOKS";
const string ItemTypeTextKeys::ITEM_TYPE_SCROLLS    = "ITEM_TYPE_SCROLLS";
const string ItemTypeTextKeys::ITEM_TYPE_WANDS      = "ITEM_TYPE_WANDS";
const string ItemTypeTextKeys::ITEM_TYPE_STAVES     = "ITEM_TYPE_STAVES";
const string ItemTypeTextKeys::ITEM_TYPE_RINGS      = "ITEM_TYPE_RINGS";
const string ItemTypeTextKeys::ITEM_TYPE_AMULETS    = "ITEM_TYPE_AMULETS";
const string ItemTypeTextKeys::ITEM_TYPE_FOOD       = "ITEM_TYPE_FOOD";
const string ItemTypeTextKeys::ITEM_TYPE_AMMUNITION = "ITEM_TYPE_AMMUNITION";
const string ItemTypeTextKeys::ITEM_TYPE_PLANTS     = "ITEM_TYPE_PLANTS";
const string ItemTypeTextKeys::ITEM_TYPE_BOATS      = "ITEM_TYPE_BOATS";
const string ItemTypeTextKeys::ITEM_TYPE_CURRENCY   = "ITEM_TYPE_CURRENCY";
const string ItemTypeTextKeys::ITEM_TYPE_TOOLS      = "ITEM_TYPE_TOOLS";

const string ItemTypeTextKeys::FOOD_TYPE_VEGETABLE  = "FOOD_TYPE_VEGETABLE";
const string ItemTypeTextKeys::FOOD_TYPE_MEAT       = "FOOD_TYPE_MEAT";
const string ItemTypeTextKeys::FOOD_TYPE_CARBS      = "FOOD_TYPE_CARBS";
const string ItemTypeTextKeys::FOOD_TYPE_DAIRY      = "FOOD_TYPE_DAIRY";
const string ItemTypeTextKeys::FOOD_TYPE_OTHER      = "FOOD_TYPE_OTHER";

// protected
const string ItemTypeTextKeys::ITEM_TYPE_MISC_SINGULAR = "ITEM_TYPE_MISC_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_WEAPON_SINGULAR = "ITEM_TYPE_WEAPON_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_ARMOUR_SINGULAR = "ITEM_TYPE_ARMOUR_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_POTION_SINGULAR = "ITEM_TYPE_POTION_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_BOOK_SINGULAR = "ITEM_TYPE_BOOK_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_SCROLL_SINGULAR = "ITEM_TYPE_SCROLL_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_WAND_SINGULAR = "ITEM_TYPE_WAND_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_STAFF_SINGULAR = "ITEM_TYPE_STAFF_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_RING_SINGULAR = "ITEM_TYPE_RING_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_AMULET_SINGULAR = "ITEM_TYPE_AMULET_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_FOOD_SINGULAR = "ITEM_TYPE_FOOD_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_AMMUNITION_SINGULAR = "ITEM_TYPE_AMMUNITION_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_PLANT_SINGULAR = "ITEM_TYPE_PLANT_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_BOAT_SINGULAR = "ITEM_TYPE_BOAT_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_CURRENCY_SINGULAR = "ITEM_TYPE_CURRENCY_SINGULAR";
const string ItemTypeTextKeys::ITEM_TYPE_TOOL_SINGULAR = "ITEM_TYPE_TOOL_SINGULAR";
