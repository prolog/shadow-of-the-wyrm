#include <boost/make_shared.hpp>
#include "ReadStrategyFactory.hpp"
#include "NullReadStrategy.hpp"
#include "ScrollReadStrategy.hpp"
#include "SpellbookReadStrategy.hpp"

ReadStrategyFactory::ReadStrategyFactory()
{
}

// Create the appropriate read strategy based on the given item type.
ReadStrategyPtr ReadStrategyFactory::create_read_strategy(const ItemType it)
{
  ReadStrategyPtr read_strategy;

  switch(it)
  {
    case ITEM_TYPE_SCROLL:
      read_strategy = boost::make_shared<ScrollReadStrategy>();
      break;
    case ITEM_TYPE_SPELLBOOK:
      read_strategy = boost::make_shared<SpellbookReadStrategy>();
      break;
    case ITEM_TYPE_NULL:
    case ITEM_TYPE_MISC:
    case ITEM_TYPE_WEAPON:
    case ITEM_TYPE_ARMOUR:
    case ITEM_TYPE_POTION:
    case ITEM_TYPE_WAND:
    case ITEM_TYPE_STAFF:
    case ITEM_TYPE_RING:
    case ITEM_TYPE_AMULET:
    case ITEM_TYPE_FOOD:
    case ITEM_TYPE_AMMUNITION:
    case ITEM_TYPE_PLANT:
    case ITEM_TYPE_BOAT:
    case ITEM_TYPE_CURRENCY:
    case ITEM_TYPE_TOOL:
    case ITEM_TYPE_LAST:
      read_strategy = boost::make_shared<NullReadStrategy>();
      break;
  }

  return read_strategy;
}
