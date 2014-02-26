#pragma once
#include "Map.hpp"
#include "XMLDataStructures.hpp"
#include "XMLWorldMapTileMapper.hpp"

// An XML reader for reading in WorldMapAreas.xml and parsing the data into an
// existing MapPtr, running any necessary Lua scripts.
class XMLWorldMapReader
{
  public:
    void read_world_map(MapPtr existing_world_map, const XMLNode& world_map_node);

  protected:
    void read_areas(MapPtr existing_world_map, const XMLNode& areas_node);
    void read_area(MapPtr existing_world_map, const XMLNode& area_node);
    void read_row(MapPtr existing_world_map, const XMLNode& row_node);

    XMLWorldMapTileMapper mapper;
};

