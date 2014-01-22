#pragma once
#include "ItemDescriber.hpp"
#include "Item.hpp"

// A class that creates an appropriate ItemDescriber based on whether or
// not the player is blind.  If the player is blind, items should just
// be "something".
class ItemDescriberFactory
{
  public:
    static ItemDescriberPtr create_item_describer(const bool player_blind, const ItemPtr item);

  protected:
    ItemDescriberFactory();
};

