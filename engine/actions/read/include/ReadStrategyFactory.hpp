#pragma once
#include "ReadStrategy.hpp"

// Class for creating an appropriate action manager for reading a certain
// type of item.  Scrolls (read and destroy) will be handled differently
// from spellbooks (read, maybe, based on skills; potentially learn the
// underlying spell; maybe destroy the spellbook after).
class ReadStrategyFactory
{
  public:
    static ReadStrategyPtr create_read_strategy(const ItemType item_type);

  protected:
    ReadStrategyFactory();
};
