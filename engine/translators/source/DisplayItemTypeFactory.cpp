#include <boost/make_shared.hpp>
#include "DisplayItemTypeFactory.hpp"
#include "StringConstants.hpp"
#include "StringTable.hpp"

using boost::make_shared;

DefaultDisplayItemType::DefaultDisplayItemType()
: DisplayItemType("?", COLOUR_WHITE, "???")
{
}

MiscDisplayItemType::MiscDisplayItemType()
: DisplayItemType("]", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_MISC))
{
}

WeaponDisplayItemType::WeaponDisplayItemType()
: DisplayItemType(")", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_WEAPONS))
{
}

ArmourDisplayItemType::ArmourDisplayItemType()
: DisplayItemType("[", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_ARMOURS))
{
}

PotionDisplayItemType::PotionDisplayItemType()
: DisplayItemType("!", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_POTIONS))
{
}

BookDisplayItemType::BookDisplayItemType()
: DisplayItemType("\"", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_BOOKS))
{
}

ScrollDisplayItemType::ScrollDisplayItemType()
: DisplayItemType("?", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_SCROLLS))
{
}

WandDisplayItemType::WandDisplayItemType()
: DisplayItemType("\\", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_WANDS))
{
}

StaffDisplayItemType::StaffDisplayItemType()
: DisplayItemType("|", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_STAVES))
{
}

RingDisplayItemType::RingDisplayItemType()
: DisplayItemType("=", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_RINGS))
{
}

AmuletDisplayItemType::AmuletDisplayItemType()
: DisplayItemType("+", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_AMULETS))
{
}

FoodDisplayItemType::FoodDisplayItemType()
: DisplayItemType("%", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_FOOD))
{
}

AmmunitionDisplayItemType::AmmunitionDisplayItemType()
: DisplayItemType("/", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_AMMUNITION))
{
}

PlantDisplayItemType::PlantDisplayItemType()
: DisplayItemType("w", COLOUR_WHITE, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_PLANTS))
{
}

// The factory that uses the above classes
DisplayItemTypeFactory::DisplayItemTypeFactory()
{
}

DisplayItemTypeFactory::~DisplayItemTypeFactory()
{
}

DisplayItemTypePtr DisplayItemTypeFactory::create(const ItemType item_type)
{
  DisplayItemTypePtr display_item_type;

  switch(item_type)
  {
    case ITEM_TYPE_MISC:
      display_item_type = make_shared<MiscDisplayItemType>();
      break;
    case ITEM_TYPE_WEAPON:
      display_item_type = make_shared<WeaponDisplayItemType>();
      break;
    case ITEM_TYPE_ARMOUR:
      display_item_type = make_shared<ArmourDisplayItemType>();
      break;
    case ITEM_TYPE_POTION:
      display_item_type = make_shared<PotionDisplayItemType>();
      break;
    case ITEM_TYPE_BOOK:
      display_item_type = make_shared<BookDisplayItemType>();
      break;
    case ITEM_TYPE_SCROLL:
      display_item_type = make_shared<ScrollDisplayItemType>();
      break;
    case ITEM_TYPE_WAND:
      display_item_type = make_shared<WandDisplayItemType>();
      break;
    case ITEM_TYPE_STAFF:
      display_item_type = make_shared<StaffDisplayItemType>();
      break;
    case ITEM_TYPE_RING:
      display_item_type = make_shared<RingDisplayItemType>();
      break;
    case ITEM_TYPE_AMULET:
      display_item_type = make_shared<AmuletDisplayItemType>();
      break;
    case ITEM_TYPE_FOOD:
      display_item_type = make_shared<FoodDisplayItemType>();
      break;
    case ITEM_TYPE_AMMUNITION:
      display_item_type = make_shared<AmmunitionDisplayItemType>();
      break;
    case ITEM_TYPE_PLANT:
      display_item_type = make_shared<PlantDisplayItemType>();
      break;
    case ITEM_TYPE_LAST:
    default:
      display_item_type = make_shared<DefaultDisplayItemType>();
      break; 
  }

  return display_item_type;
}

#ifdef UNIT_TESTS
#include "unit_tests/DisplayItemTypeFactory_test.cpp"
#endif
