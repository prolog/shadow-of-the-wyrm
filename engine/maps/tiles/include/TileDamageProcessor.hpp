#pragma once
#include "Tile.hpp"

// TileDamageProcessor is responsible for applying a particular damage
// type to a tile.  In practical terms, this involves checking to see if
// any items are potentially destroyed, checking to see whether they're
// actually destroyed, and then destroying them.
class TileDamageProcessor
{
  public:
    void process(TilePtr tile, CreaturePtr creature);

  protected:
    virtual std::string get_message_sid() const;
    virtual int get_pct_chance() const;
    virtual bool affects_item(ItemPtr item) = 0;
    virtual std::string get_item_destruction_message(ItemPtr item);
};

using TileDamageProcessorPtr = std::shared_ptr<TileDamageProcessor>;

