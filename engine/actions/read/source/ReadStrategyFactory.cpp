#include "ReadStrategyFactory.hpp"
#include "NullReadStrategy.hpp"
#include "ScrollReadStrategy.hpp"
#include "SpellbookReadStrategy.hpp"
#include "TextReadStrategy.hpp"

using namespace std;

ReadStrategyFactory::ReadStrategyFactory()
{
}

// Create the appropriate read strategy based on the given item type.
ReadStrategyPtr ReadStrategyFactory::create_read_strategy(const ItemType it, const string& text_sid)
{
  ReadStrategyPtr read_strategy;

  if (!text_sid.empty())
  {
    read_strategy = std::make_shared<TextReadStrategy>();
  }
  else
  {
    switch(it)
    {
      case ItemType::ITEM_TYPE_SCROLL:
        read_strategy = std::make_shared<ScrollReadStrategy>();
        break;
      case ItemType::ITEM_TYPE_SPELLBOOK:
        read_strategy = std::make_shared<SpellbookReadStrategy>();
        break;
      case ItemType::ITEM_TYPE_NULL:
      case ItemType::ITEM_TYPE_MISC:
      case ItemType::ITEM_TYPE_WEAPON:
      case ItemType::ITEM_TYPE_ARMOUR:
      case ItemType::ITEM_TYPE_POTION:
      case ItemType::ITEM_TYPE_WAND:
      case ItemType::ITEM_TYPE_STAFF:
      case ItemType::ITEM_TYPE_RING:
      case ItemType::ITEM_TYPE_AMULET:
      case ItemType::ITEM_TYPE_FOOD:
      case ItemType::ITEM_TYPE_AMMUNITION:
      case ItemType::ITEM_TYPE_PLANT:
      case ItemType::ITEM_TYPE_BOAT:
      case ItemType::ITEM_TYPE_CURRENCY:
      case ItemType::ITEM_TYPE_TOOL:
      case ItemType::ITEM_TYPE_LAST:
        read_strategy = std::make_shared<NullReadStrategy>();
        break;
    }
  }

  return read_strategy;
}
