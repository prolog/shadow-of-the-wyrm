#include "ItemDescriberFactory.hpp"
#include "ItemDescriber.hpp"
#include "BlindItemDescriber.hpp"

ItemDescriberFactory::ItemDescriberFactory()
{
}

ItemDescriberPtr ItemDescriberFactory::create_item_describer(const bool player_blind, ItemPtr item)
{
  ItemDescriberPtr describer;

  if (player_blind)
  {
    if (!(item && item->get_glowing()))
    {
      describer = std::make_shared<BlindItemDescriber>();
    }
  }
  
  if (!describer)
  {
    describer = std::make_shared<ItemDescriber>(item);
  }

  return describer;
}

