#include <algorithm>
#include "DisplayItemTypeFactory.hpp"
#include "ItemTypeTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

DefaultDisplayItemType::DefaultDisplayItemType()
  : DisplayItemType("?", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_NULL, "???")
{
}

MiscDisplayItemType::MiscDisplayItemType()
  : DisplayItemType("]", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_MISC, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_MISC))
{
}

WeaponDisplayItemType::WeaponDisplayItemType()
  : DisplayItemType(")", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_WEAPON, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_WEAPONS))
{
}

ArmourDisplayItemType::ArmourDisplayItemType()
  : DisplayItemType("[", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_ARMOUR, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_ARMOURS))
{
}

PotionDisplayItemType::PotionDisplayItemType()
  : DisplayItemType("!", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_POTION, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_POTIONS))
{
}

BookDisplayItemType::BookDisplayItemType()
  : DisplayItemType("\"", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_SPELLBOOK, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_BOOKS))
{
}

ScrollDisplayItemType::ScrollDisplayItemType()
  : DisplayItemType("?", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_SCROLL, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_SCROLLS))
{
}

WandDisplayItemType::WandDisplayItemType()
  : DisplayItemType("\\", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_WAND, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_WANDS))
{
}

StaffDisplayItemType::StaffDisplayItemType()
  : DisplayItemType("|", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_STAFF, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_STAVES))
{
}

RingDisplayItemType::RingDisplayItemType()
  : DisplayItemType("=", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_RING, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_RINGS))
{
}

AmuletDisplayItemType::AmuletDisplayItemType()
  : DisplayItemType("+", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_AMULET, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_AMULETS))
{
}

FoodDisplayItemType::FoodDisplayItemType()
  : DisplayItemType("%%", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_FOOD, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_FOOD))
{
}

AmmunitionDisplayItemType::AmmunitionDisplayItemType()
  : DisplayItemType("/", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_AMMUNITION, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_AMMUNITION))
{
}

PlantDisplayItemType::PlantDisplayItemType()
  : DisplayItemType("#", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_PLANT, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_PLANTS))
{
}

BoatDisplayItemType::BoatDisplayItemType()
  : DisplayItemType("&", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_BOAT, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_BOATS))
{
}

CurrencyDisplayItemType::CurrencyDisplayItemType()
  : DisplayItemType("$", Colour::COLOUR_BOLD_YELLOW, ItemType::ITEM_TYPE_CURRENCY, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_CURRENCY))
{
}

ToolsDisplayItemType::ToolsDisplayItemType()
  : DisplayItemType("(", Colour::COLOUR_WHITE, ItemType::ITEM_TYPE_TOOL, StringTable::get(ItemTypeTextKeys::ITEM_TYPE_TOOLS))
{
}

// The factory that uses the above classes
map<ItemType, DisplayItemTypePtr> DisplayItemTypeFactory::display_map;

DisplayItemTypeFactory::DisplayItemTypeFactory()
{
}

DisplayItemTypeFactory::~DisplayItemTypeFactory()
{
}

void DisplayItemTypeFactory::initialize_map()
{
  display_map.clear();

  DisplayItemTypePtr di = std::make_shared<MiscDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_NULL, di));
  display_map.insert(make_pair(ITEM_TYPE_MISC, di));

  di = std::make_shared<WeaponDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_WEAPON, di));

  di = std::make_shared<ArmourDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_ARMOUR, di));

  di = std::make_shared<PotionDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_POTION, di));

  di = std::make_shared<BookDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_SPELLBOOK, di));

  di = std::make_shared<ScrollDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_SCROLL, di));

  di = std::make_shared<WandDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_WAND, di));

  di = std::make_shared<StaffDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_STAFF, di));

  di = std::make_shared<RingDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_RING, di));

  di = std::make_shared<AmuletDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_AMULET, di));

  di = std::make_shared<FoodDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_FOOD, di));

  di = std::make_shared<AmmunitionDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_AMMUNITION, di));

  di = std::make_shared<PlantDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_PLANT, di));

  di = std::make_shared<BoatDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_BOAT, di));

  di = std::make_shared<CurrencyDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_CURRENCY, di));

  di = std::make_shared<ToolsDisplayItemType>();
  display_map.insert(make_pair(ITEM_TYPE_TOOL, di));
}

DisplayItemTypePtr DisplayItemTypeFactory::create(const int item_symbol)
{
  DisplayItemTypePtr display_item_type = std::make_shared<DefaultDisplayItemType>();

  if (display_map.empty())
  {
    initialize_map();
  }

  auto iter = find_if(display_map.begin(), display_map.end(), [item_symbol] (pair<ItemType, DisplayItemTypePtr> iter) {return iter.second->get_symbol().at(0) == item_symbol;});
  
  if (iter != display_map.end())
  {
    display_item_type = iter->second;
  }

  return display_item_type;
}

DisplayItemTypePtr DisplayItemTypeFactory::create(const ItemType item_type)
{
  static_assert(ITEM_TYPE_LAST == 16, "Unexpected final item type - update mapping in DisplayItemTypeFactory.");
  if (display_map.empty())
  {
    initialize_map();
  }

  // Copy the cached value, and return it.
  DisplayItemTypePtr display_item_type = std::make_shared<DisplayItemType>(*display_map.find(item_type)->second);

  return display_item_type;
}

#ifdef UNIT_TESTS
#include "unit_tests/DisplayItemTypeFactory_test.cpp"
#endif
