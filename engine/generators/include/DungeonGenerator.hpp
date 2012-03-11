#pragma once
#include "Generator.hpp"
#include "Map.hpp"
#include <map>

// Used to generate the both room and its initial inhabitants.
enum DungeonFeature
{
  DUNGEON_FEATURE_MIN = 0
, DUNGEON_FEATURE_ROOM = 0
, DUNGEON_FEATURE_CIRCULAR_WITH_PIT = 1 // Fall through to next dungeon level, take damage
, DUNGEON_FEATURE_CAVE_IN = 2
, DUNGEON_FEATURE_VAULT = 3
, DUNGEON_FEATURE_OUT_OF_DEPTH_VAULT = 4
, DUNGEON_FEATURE_BEEHIVE = 5
, DUNGEON_FEATURE_ZOO = 6
, DUNGEON_FEATURE_MAX = 6
};

// JCD FIXME refactor later
class Room
{
  public:
  Room();
  Room(int nid, int nx1, int nx2, int ny1, int ny2);
  bool operator==(const Room& that);

  boost::shared_ptr<Room> centre_room;
  bool contains(Coordinate c) const;
  Coordinate get_centre() const;
  
  int id;
  int x1;
  int x2;
  int y1;
  int y2;
};

typedef std::map<DungeonFeature, std::pair<const int, const int> > DungeonFeatureSizeMap;
typedef std::map<DungeonFeature, std::pair<const int, const int> >::iterator DungeonFeatureSizeMapIterator;
typedef std::map<DungeonFeature, std::pair<const int, const int> >::const_iterator DungeonFeatureSizeMapIterator_const;

class DungeonGenerator : public Generator
{
  public:
    DungeonGenerator();
    virtual MapPtr generate(const Dimensions& dim, const std::string& map_exit_id);

  protected:
    virtual bool    generate_dungeon(MapPtr map);
    virtual TilePtr generate_tile(MapPtr current_map, int row, int col);

    // Corridor and feature creation routines.

    // Corridor and feature placement routines.  True if the attempt succeeded, false otherwise.
    virtual bool    check_range(MapPtr map, int start_row, int start_col, int size_rows, int size_cols);
    virtual bool    place_feature(MapPtr map, const DungeonFeature feature_type, int start_row, int start_col, int size_rows, int size_cols);
    virtual bool    place_room(MapPtr map, int start_row, int start_col, int size_rows, int size_cols);
    virtual bool    add_additional_corridors(MapPtr map);
    virtual bool    place_doorway(MapPtr map, int row, int col);
    virtual bool    place_doorways(MapPtr current_map);
    virtual bool    place_staircases(MapPtr current_map);

    // Helpers.
    virtual DungeonFeature get_random_feature();
    virtual int get_min_feature_height(const DungeonFeature feature);
    virtual int get_max_feature_height(const DungeonFeature feature);
    virtual int get_min_feature_width(const DungeonFeature feature);
    virtual int get_max_feature_width(const DungeonFeature feature);

    // Initialization
    virtual void initialize_height_and_width_maps();

    const int DEFAULT_MIN_HEIGHT;
    const int DEFAULT_MAX_HEIGHT;
    const int DEFAULT_MIN_WIDTH;
    const int DEFAULT_MAX_WIDTH;
    const int SPACE_BETWEEN_FEATURES;

    std::map<DungeonFeature, std::pair<const int, const int> > feature_width_map;
    std::map<DungeonFeature, std::pair<const int, const int> > feature_height_map;
    
    std::vector<Room> unconnected_rooms;
    std::vector<Room> connected_rooms;
    std::vector<int> y1_cheaty_vector;
    std::vector<int> y2_cheaty_vector;
    
    bool connect_rooms(MapPtr map, const Room& room1, const Room& room2);
    bool is_tile_adjacent_to_room_tile(const Dimensions& dim, const int row, const int col);
    bool tile_exists_outside_of_room(const int row, const int col, const bool check_connected, const bool check_unconnected);
};
