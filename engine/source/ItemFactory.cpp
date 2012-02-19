#include "ItemFactory.hpp"

ItemFactory::ItemFactory()
{
}

ItemFactory::~ItemFactory()
{
}

ItemPtr ItemFactory::create(ItemPtr item_to_copy)
{
  ItemPtr new_item;
  
  if (item_to_copy)
  {
    new_item = ItemPtr(item_to_copy->clone());
  }
  
  return new_item;
}
