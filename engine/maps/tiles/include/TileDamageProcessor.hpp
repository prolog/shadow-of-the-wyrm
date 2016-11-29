#pragma once
#include "Tile.hpp"

// TileDamageProcessor is responsible for applying a particular damage
// type to a tile.  In practical terms, this involves checking to see if
// any items are potentially destroyed, checking to see whether they're
// actually destroyed, and then destroying them.
class TileDamageProcessor
{
  public:
    void process(TilePtr tile);

  protected:
    virtual bool affects_item(ItemPtr item) = 0;
};

using TileDamageProcessorPtr = std::shared_ptr<TileDamageProcessor>;

