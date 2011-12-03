#pragma once
#include <vector>
#include <boost/shared_ptr.hpp>
#include "tiles.hpp"
#include "Creature.hpp"
#include "Item.hpp"

class Tile
{
  public:
    Tile();

    virtual void set_illuminated(bool new_illuminated);
    virtual bool get_illuminated() const;

    // This is player-centric.  Probably OK for now, but may need to be
    // revisited later.
    virtual void set_explored(bool new_explored);
    virtual bool get_explored() const;

    virtual void set_creature(const CreaturePtr& new_creature);
    virtual CreaturePtr get_creature() const;

    virtual TileType get_tile_type() const;

  protected:
    virtual void set_default_properties();

    bool illuminated;
    bool explored;

    // This is defined by each class, and shouldn't be overridden
    // by means of a set function.
    TileType tile_type;

    // Each tile can have at most one creature on it.
    CreaturePtr creature;
    
    // Each tile can have any number of items piled up on it.
    std::vector<ItemPtr> items;
};

typedef boost::shared_ptr<Tile> TilePtr;
