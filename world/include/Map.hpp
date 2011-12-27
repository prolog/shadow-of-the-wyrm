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

		// These functions work on a list built up from the map itself.
		// This allows for quicker lookup.
		CreaturePtr get_creature(const uint idx_in_creature_list);
		std::vector<CreaturePtr> get_creatures();
		// Other get_creature... fns here.
		// Other remove_creature... fns here.

		bool insert(int row, int col, TilePtr tile);
		TilePtr at(int row, int col);

		void set_size(const Dimensions& new_dimensions);
		Dimensions size() const;

		std::map<Coordinate, TilePtr > get_tiles() const;

    void clear_locations();
    void add_location(const std::string& location, const Coordinate& coordinate);
    Coordinate get_location(const std::string& location) const;
    TilePtr get_tile_at_location(const std::string& location);

	protected:
		void create_creatures();

    // NOTE: This information is also stored at the Tile level, but since it's a shared_ptr, that's okay.
    // Ensure that when creatures are created or killed, both data structures are updated accordingly.
    std::vector<CreaturePtr> creatures;

		std::map<Coordinate, TilePtr > tiles;
		Dimensions dimensions;
    NamedMapLocations locations;
};

typedef boost::shared_ptr<Map> MapPtr;

