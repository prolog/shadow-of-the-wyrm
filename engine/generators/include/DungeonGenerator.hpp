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

typedef std::map<DungeonFeature, std::pair<const int, const int> > DungeonFeatureSizeMap;
typedef std::map<DungeonFeature, std::pair<const int, const int> >::iterator DungeonFeatureSizeMapIterator;
typedef std::map<DungeonFeature, std::pair<const int, const int> >::const_iterator DungeonFeatureSizeMapIterator_const;

class DungeonGenerator : public Generator
{
  public:
    DungeonGenerator();
    virtual MapPtr generate(const Dimensions& dim, const std::string& map_exit_id);

  protected:
    virtual MapPtr  generate_dungeon(MapPtr map);
    virtual TilePtr generate_tile(MapPtr current_map, int row, int col);

    // Corridor and feature placement routines.
    virtual void    place_feature(MapPtr map, const DungeonFeature feature_type, int start_row, int start_col, int size_rows, int size_cols);
    virtual void    place_room(MapPtr map, int start_row, int start_col, int size_rows, int size_cols);
    virtual void    place_doorway(MapPtr map, int row, int col);
    virtual void    place_staircases(MapPtr current_map);

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
};
