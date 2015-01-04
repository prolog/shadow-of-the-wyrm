#include "ItemFactory.hpp"
#include "RNG.hpp"

ItemFactory::ItemFactory()
{
}

ItemFactory::~ItemFactory()
{
}

// Create a new item with a new ID and a random status.
ItemPtr ItemFactory::create(ItemPtr item_to_copy)
{
  ItemPtr new_item;
  
  if (item_to_copy)
  {
    new_item = ItemPtr(item_to_copy->create_with_new_id());
    randomize_item_status(new_item);
  }
  
  return new_item;
}

// Randomize the status of an existing item.
void ItemFactory::randomize_item_status(ItemPtr item)
{
  int pct = RNG::range(1, 100);
  ItemStatus status;

  if (pct <= 5)
  {
    status = ItemStatus::ITEM_STATUS_CURSED;
  }
  else if (pct <= 93)
  {
    status = ItemStatus::ITEM_STATUS_UNCURSED;
  }
  else
  {
    status = ItemStatus::ITEM_STATUS_BLESSED;
  }

  item->set_status(status);
}