#pragma once

#include <vector>
#include <map>
#include <boost/shared_ptr.hpp>
#include "common.hpp"
#include "Dimensions.hpp"
#include "Tile.hpp"


// JCD FIXME: Before delving too deep into things, it might be nice to  make this pair<int,int,int>
// to represent a truly three dimensional map.  Maybe for v0.2.0?
typedef std::map<std::string, Coordinate> NamedMapLocations;

class Map
{
	public:
    Map(const Map& new_map);
		Map(const Dimensions& new_dimensions);
		bool insert(int row, int col, TilePtr tile);
		TilePtr at(int row, int col);
		void set_size(const Dimensions& new_dimensions);
		Dimensions size() const;
		std::map<Coordinate, TilePtr > get_tiles() const;

    void clear_locations();
    void add_location(const std::string& location, const Coordinate& coordinate);
    TilePtr get_tile_at_location(const std::string& location);

	protected:
		std::map<Coordinate, TilePtr > tiles;
		Dimensions dimensions;
    NamedMapLocations locations;
};

typedef boost::shared_ptr<Map> MapPtr;

