#pragma once

#include <vector>
#include <map>
#include "common.hpp"
#include "Dimensions.hpp"
#include "Tile.hpp"

#include <boost/shared_ptr.hpp>
class Map
{
	public:
    Map(const Map& new_map);
		Map(const Dimensions& new_dimensions);
		bool insert(int row, int col, TilePtr tile);
		TilePtr at(int row, int col);
		void set_size(const Dimensions& new_dimensions);
		Dimensions size() const;
		std::map<std::pair<int, int>, TilePtr > get_tiles() const;

	protected:
		std::map<std::pair<int, int>, TilePtr > tiles;
		Dimensions dimensions;
};

typedef boost::shared_ptr<Map> MapPtr;

// JCD FIXME: Before delving too deep into things, it might be nice to  make this pair<int,int,int>
// to represent a truly three dimensional map.  Maybe for v0.2.0?
typedef std::pair<int, int> Coordinate;
