#include <boost/make_shared.hpp>
#include "ItemDescriberFactory.hpp"
#include "ItemDescriber.hpp"
#include "BlindItemDescriber.hpp"

ItemDescriberFactory::ItemDescriberFactory()
{
}

IDescriberPtr ItemDescriberFactory::create_item_describer(const bool player_blind, ItemPtr item)
{
  IDescriberPtr describer;

  if (player_blind)
  {
    if (!(item && item->get_glowing()))
    {
      describer = boost::make_shared<BlindItemDescriber>();
    }
  }
  
  if (!describer)
  {
    describer = boost::make_shared<ItemDescriber>(item);
  }

  return describer;
}

