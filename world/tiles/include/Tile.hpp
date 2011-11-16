#pragma once

#include "tiles.hpp"
#include <boost/shared_ptr.hpp>

class Tile
{
  public:
    Tile();

    virtual void set_illuminated(bool new_illuminated);
    virtual bool get_illuminated() const;

    virtual void set_explored(bool new_explored);
    virtual bool get_explored() const;

    virtual TileType get_tile_type() const;

  protected:
    virtual void set_default_properties();

    bool illuminated;
    bool explored;

    // This is defined by each class, and shouldn't be overridden
    // by means of a set function.
    TileType tile_type;
};

typedef boost::shared_ptr<Tile> TilePtr;
