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
    describer = boost::make_shared<BlindItemDescriber>();
  }
  else
  {
    describer = boost::make_shared<ItemDescriber>(item);
  }

  return describer;
}

