#pragma once
#include "XMLTileMapper.hpp"

// Does the tile mappings required for WorldMapAreas.xml - these will be
// world map tiles (forest, field, sea, etc) rather than overworld/
// underworld specific mappings.
//
// Basically, this allows re-using symbols because I'd prefer not to use
// weird symbols (extended ascii/unicord/etc) if I don't have to.
class XMLWorldMapTileMapper : public XMLTileMapper
{
  public:
    XMLWorldMapTileMapper();

    virtual TilePtr create_tile(const char xml_tile);
};
