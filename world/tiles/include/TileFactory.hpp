#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Tile.hpp"

using TileSerializationMap = std::map<ClassIdentifier, TilePtr>;

class TileFactory
{
  public:
    static TilePtr create_tile(const ClassIdentifier tile_clid);

  protected:
    static void initialize_tile_map();

    TileFactory();
    ~TileFactory();

    static TileSerializationMap tiles_map;
};

