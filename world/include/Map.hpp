#pragma once
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include "common.hpp"
#include "Dimensions.hpp"
#include "ISerializable.hpp"
#include "Tile.hpp"
#include "MapExit.hpp"
#include "MapTypes.hpp"
#include "TileTransform.hpp"

// Forward declarations.
class Creature;
class Tile;

using TilesContainer = std::unordered_map<std::string, std::shared_ptr<Tile>>;
using TileTransformContainer = std::map<double, std::vector<TileTransform>>;

class Map : public ISerializable
{
	public:
    Map(const Map& new_map);
		Map(const Dimensions& new_dimensions, const Dimensions& original_dimensions = Dimensions());
    bool operator==(const Map& map) const;
		
		// Functions used when creating a view map - reset the
		// creatures and locations after copying the map.
		void reset_creatures_and_locations();

		// These functions work on a list built up from the map itself.
		// This allows for quicker lookup.
		bool has_creature(const std::string& creature_id);
		std::shared_ptr<Creature> get_creature(const std::string& creature_id);
		std::map<std::string, std::shared_ptr<Creature>> get_creatures();
		std::map<std::string, std::shared_ptr<Creature>>& get_creatures_ref();

    std::map<Direction, std::vector<Coordinate>>& get_tile_exits_ref();
    std::map<Direction, std::vector<Coordinate>> get_tile_exits() const;

    void add_creature(std::shared_ptr<Creature> creature);
		void remove_creature(const std::string& creature_id);
		// Other get_creature... fns here.
		// Other remove_creature... fns here.

    // Shouldn't generally be called - used by the XML readers to directly set
    // the tiles.
    void set_tiles(const TilesContainer& new_tiles);

		bool insert(int row, int col, std::shared_ptr<Tile> tile);
    bool insert(const Coordinate& c, std::shared_ptr<Tile> tile);

		std::shared_ptr<Tile> at(int row, int col);
		std::shared_ptr<Tile> at(const Coordinate& c);

		void set_size(const Dimensions& new_dimensions);
		Dimensions size() const;
    Dimensions& size_ref();
		
		// If the map is not a view map, this will return the same as
		// size().  If the map is a view map, this will return the map's
		// original dimensions, as if it were a "regular" map.
    void set_original_size(const Dimensions& new_original_dimensions);
		Dimensions original_size() const;
    Dimensions& original_size_ref();
		
		void set_terrain_type(const TileType new_terrain_type);
		TileType get_terrain_type() const;

		void set_map_type(const MapType& new_type);
		MapType get_map_type() const;
		
		TilesContainer get_tiles() const;

    void clear_locations();
    void add_or_update_location(const std::string& location, const Coordinate& coordinate);
    void remove_location(const std::string& location);
    bool has_location(const std::string& location);
    Coordinate get_location(const std::string& location) const;
    std::shared_ptr<Tile> get_tile_at_location(const std::string& location);
    
    void set_map_exit(MapExitPtr new_map_exit);
    MapExitPtr get_map_exit() const;
    
    void set_map_id(const std::string& new_map_id);
    std::string get_map_id() const;
    
    std::string get_map_exit_id() const;
    
    void set_permanent(const bool permenance);
    bool get_permanent() const;

    // Set/get the base danger level.  This is used to determine the danger of the monsters to
    // generate, as well as the quality of the items.
    void set_danger(const int new_danger);
    int get_danger() const;

    // Set/get whether creature updates are allowed.  If this is true, then
    // the engine will periodically add additional creatures to the map while
    // this map is active.  This will generally be true of maps generated
    // in-game, and false for maps defined in the custom XML files.
    void set_allow_creature_updates(const bool new_allow_creature_updates);
    bool get_allow_creature_updates() const;

    void set_property(const std::string& prop, const std::string& value);
    bool remove_property(const std::string& prop);
    void set_properties(const std::map<std::string, std::string>& new_properties);
    std::string get_property(const std::string& prop) const;
    std::map<std::string, std::string> get_properties() const;

    void set_tile_transforms(const TileTransformContainer& new_tile_transforms);
    TileTransformContainer& get_tile_transforms_ref();
    TileTransformContainer get_tile_transforms() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

		void create_creatures();		

	protected:
    friend class SL_Engine_Map;
    
    // NOTE: This information is also stored at the Tile level, but since it's a shared_ptr, that's okay.
    // Ensure that when creatures are created or killed, both data structures are updated accordingly.
    std::map<std::string, std::shared_ptr<Creature>> creatures;

    // These reference the versions stored at the tile level, and are kept
    // at the map level so that quick lookup by direction is possible.
    std::map<Direction, std::vector<Coordinate>> tile_exits;

    TilesContainer tiles;
    Dimensions dimensions;
    Dimensions original_dimensions;
    NamedMapLocations locations;
    TileType terrain_type; // field, forest, village, etc.
    MapType map_type;
    MapExitPtr map_exit;
    std::string map_id;
    bool permanent;
    int danger;
    bool allow_creature_updates;
    std::map<std::string, std::string> properties;
    TileTransformContainer tile_transforms;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using MapPtr = std::shared_ptr<Map>;
