#pragma once
#include <string>
#include <map>
#include <vector>
#include <unordered_map>
#include "common.hpp"
#include "Dimensions.hpp"
#include "ISerializable.hpp"
#include "MapExit.hpp"
#include "MapTypes.hpp"
#include "ScriptDetails.hpp"
#include "Shop.hpp"
#include "Tile.hpp"
#include "TileTransform.hpp"
#include "Weather.hpp"

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

    // Function used when loading a map - reset the creatures
    // and the creature locations (but not all locations).
    void reset_creatures_and_creature_locations();

		// These functions work on a list built up from the map itself.
		// This allows for quicker lookup.
		bool has_creature(const std::string& creature_id);
    bool has_player();
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

		std::shared_ptr<Tile> at(int row, int col) const;
		std::shared_ptr<Tile> at(const Coordinate& c) const;

    void set_name_sid(const std::string& new_name_sid);
    std::string get_name_sid() const;

    void set_default_race_id(const std::string& new_default_race_id);
    std::string get_default_race_id() const;

    void set_default_deity_id(const std::string& new_default_deity_id);
    std::string get_default_deity_id() const;

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
		TilesContainer& get_tiles_ref();

    void set_is_water_shallow(const bool new_shallow);
    bool get_is_water_shallow() const;
    void set_is_open_sky(const bool new_open_sky);
    bool get_is_open_sky() const;

    void clear_locations();
    void add_or_update_location(const std::string& location, const Coordinate& coordinate);
    void remove_location(const std::string& location);
    bool has_location(const std::string& location);
    Coordinate get_location(const std::string& location) const;
    std::pair<Coordinate, std::shared_ptr<Tile>> get_location_and_tile(const std::string& location) const;
    std::map<std::string, Coordinate> get_locations() const;
    std::shared_ptr<Tile> get_tile_at_location(const std::string& location);
    
    // "Edge" map directions.  Cardinal directions only for now.
    void set_default_map_exit(MapExitPtr new_map_exit);
    void set_map_exit(MapExitPtr new_map_exit);
    void set_map_exit(const Direction d, MapExitPtr new_map_exit);
    std::map<Direction, MapExitPtr> get_map_exits() const;
    MapExitPtr get_map_exit() const;
    MapExitPtr get_map_exit(const Direction d) const;
    
    void set_map_id(const std::string& new_map_id);
    std::string get_map_id() const;
    
    bool get_is_multi_map() const;
    std::string get_map_exit_id() const;
    std::string get_map_exit_id(const Direction d) const;
    
    void set_permanent(const bool permenance);
    bool get_permanent() const;

    // Set/get the base danger level.  This is used to determine the danger of the monsters to
    // generate, as well as the quality of the items.
    void set_danger(const int new_danger);
    int get_danger() const;

    // Set/get whether creature initialization is allowed.  Normally this is
    // always true, but there are certain maps where we want to suppress
    // creature generation altogether, and do so by setting a flag while
    // the map is generating.  This is the flag that controls that.
    void set_allow_creature_creation(const bool new_allow_creature_creation);
    bool get_allow_creature_creation() const;

    // Set/get whether creature updates are allowed.  If this is true, then
    // the engine will periodically add additional creatures to the map while
    // this map is active.  This will generally be true of maps generated
    // in-game, and false for maps defined in the custom XML files.
    void set_allow_creature_updates(const bool new_allow_creature_updates);
    bool get_allow_creature_updates() const;

    void set_property(const std::string& prop, const std::string& value);
    bool remove_property(const std::string& prop);
    void set_properties(const std::map<std::string, std::string>& new_properties);
    bool has_property(const std::string& prop) const;
    std::string get_property(const std::string& prop) const;
    std::map<std::string, std::string> get_properties() const;

    void set_tile_transforms(const TileTransformContainer& new_tile_transforms);
    TileTransformContainer& get_tile_transforms_ref();
    TileTransformContainer get_tile_transforms() const;

    void set_preset_locations(const std::vector<Coordinate>& new_preset_locations);
    std::vector<Coordinate> get_preset_locations() const;
    std::vector<Coordinate>& get_preset_locations_ref();

    // Returns the range over which creatures and items
    // can be generated.  Usually ranges from (0,0) to
    // (row-1,col-1) but this may change depending on the
    // value set by the generator, as an additional property.
    std::pair<Coordinate, Coordinate> get_generation_coordinates() const;

    void set_shops(const std::map<std::string, Shop>& new_shops);
    std::map<std::string, Shop>& get_shops_ref();
    std::map<std::string, Shop> get_shops() const;
    bool has_shop(const std::string& shop_id) const;

    void clear_event_scripts();
    void set_event_scripts(const EventScriptsMap& esm);
    EventScriptsMap get_event_scripts() const;
    EventScriptsMap& get_event_scripts_ref();
    void add_event_script(const std::string& event_name, const ScriptDetails& sd);
    bool has_event_script(const std::string& event_name);
    ScriptDetails get_event_script(const std::string& event_name) const;

    void set_weather(const Weather& new_weather);
    Weather& get_weather_ref();
    Weather get_weather() const;

    Coordinate get_starting_location() const;

    void set_secondary_terrain(const std::vector<TileType>& new_secondary_terrain);
    void add_secondary_terrain(const TileType tt);

    std::vector<Direction> get_coastline_directions() const;
    bool is_islet() const;

    std::vector<TileType> get_secondary_terrain() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

		void create_creatures();		

	protected:
    friend class SW_Engine_Map;
    
    // NOTE: This information is also stored at the Tile level, but since it's a shared_ptr, that's okay.
    // Ensure that when creatures are created or killed, both data structures are updated accordingly.
    std::map<std::string, std::shared_ptr<Creature>> creatures;

    // These reference the versions stored at the tile level, and are kept
    // at the map level so that quick lookup by direction is possible.
    std::map<Direction, std::vector<Coordinate>> tile_exits;

    TilesContainer tiles;
    std::string name_sid;
    std::string default_race_id;
    std::string default_deity_id;
    Dimensions dimensions;
    Dimensions original_dimensions;
    NamedMapLocations locations;
    TileType terrain_type; // field, forest, village, etc.
    MapType map_type;
    std::map<Direction, MapExitPtr> map_exits;
    std::string map_id;
    bool permanent;
    int danger;
    bool allow_creature_creation;
    bool allow_creature_updates;
    std::map<std::string, std::string> properties;
    TileTransformContainer tile_transforms;
    std::vector<Coordinate> preset_locations; // used for generating creatures onto specific locations
    std::map<std::string, Shop> shops;
    EventScriptsMap event_scripts;
    Weather weather;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

using MapPtr = std::shared_ptr<Map>;
