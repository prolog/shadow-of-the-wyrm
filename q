[1mdiff --git a/engine/generators/source/GeneratorUtils.cpp b/engine/generators/source/GeneratorUtils.cpp[m
[1mindex bd1a1da12..5aa37e794 100644[m
[1m--- a/engine/generators/source/GeneratorUtils.cpp[m
[1m+++ b/engine/generators/source/GeneratorUtils.cpp[m
[36m@@ -639,6 +639,11 @@[m [mvoid GeneratorUtils::generate_coastline(MapPtr map, const Generator * const gene[m
     if (generate_east) map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_EAST, to_string(true));[m
     if (generate_west) map->set_property(MapProperties::MAP_PROPERTIES_COASTLINE_WEST, to_string(true));[m
 [m
[32m+[m[32m    if (generate_north || generate_south || generate_east || generate_west)[m
[32m+[m[32m    {[m
[32m+[m[32m      map->add_secondary_terrain(TileType::TILE_TYPE_SEA);[m
[32m+[m[32m    }[m
[32m+[m
     CoastlineGenerator cg;[m
     cg.generate(map, generate_north, generate_south, generate_east, generate_west);[m
   }[m
[1mdiff --git a/engine/maps/source/MapUtils.cpp b/engine/maps/source/MapUtils.cpp[m
[1mindex 07b7ba735..82f255422 100644[m
[1m--- a/engine/maps/source/MapUtils.cpp[m
[1m+++ b/engine/maps/source/MapUtils.cpp[m
[36m@@ -109,7 +109,12 @@[m [mbool MapUtils::is_coordinate_within_player_restricted_zone(MapPtr map, const Coo[m
 //   feature details)[m
 bool MapUtils::is_tile_available_for_creature(CreaturePtr creature, TilePtr tile)[m
 {[m
[31m-  return tile && !is_creature_present(tile) && !tile->get_is_blocking(creature);[m
[32m+[m[32m  if (creature == nullptr) return false;[m
[32m+[m[32m  bool breathes_ok = (tile->get_water_type() == WaterType::WATER_TYPE_UNDEFINED || creature->can_breathe(BreatheType::BREATHE_TYPE_WATER));[m
[32m+[m
[32m+[m[32m  return tile && !is_creature_present(tile)[m[41m [m
[32m+[m[32m              && breathes_ok[m
[32m+[m[32m              && !tile->get_is_blocking(creature);[m
 }[m
 [m
 // Check to see if a tile is available for an item by checking:[m
[1mdiff --git a/engine/maps/source/unit_tests/Map_test.cpp b/engine/maps/source/unit_tests/Map_test.cpp[m
[1mindex 54cdfba76..83f5fbfb0 100644[m
[1m--- a/engine/maps/source/unit_tests/Map_test.cpp[m
[1m+++ b/engine/maps/source/unit_tests/Map_test.cpp[m
[36m@@ -216,3 +216,65 @@[m [mTEST_F(SW_Engine_Map, get_starting_location)[m
 [m
   EXPECT_EQ(exp, map->get_starting_location());[m
 }[m
[32m+[m
[32m+[m[32mTEST_F(SW_Engine_Map, set_secondary_terrain)[m
[32m+[m[32m{[m
[32m+[m[32m  vector<TileType> tts = { TileType::TILE_TYPE_SEA, TileType::TILE_TYPE_DESERT };[m
[32m+[m[32m  MapPtr map = make_map();[m
[32m+[m[32m  map->set_secondary_terrain(tts);[m
[32m+[m[32m  vector<TileType> tts_new = map->get_secondary_terrain();[m
[32m+[m
[32m+[m[32m  EXPECT_EQ(2, tts_new.size());[m
[32m+[m
[32m+[m[32m  for (const auto tt : tts)[m
[32m+[m[32m  {[m
[32m+[m[32m    EXPECT_TRUE(std::find(tts_new.begin(), tts_new.end(), tt) != tts_new.end());[m
[32m+[m[32m  }[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mTEST_F(SW_Engine_Map, add_secondary_terrain)[m
[32m+[m[32m{[m
[32m+[m[32m  vector<TileType> tts = { TileType::TILE_TYPE_SEA, TileType::TILE_TYPE_DESERT };[m
[32m+[m[32m  MapPtr map = make_map();[m
[32m+[m
[32m+[m[32m  for (int i = 0; i < 3; i++)[m
[32m+[m[32m  {[m
[32m+[m[32m    for (const auto tt : tts)[m
[32m+[m[32m    {[m
[32m+[m[32m      map->add_secondary_terrain(tt);[m
[32m+[m[32m    }[m
[32m+[m[32m  }[m
[32m+[m
[32m+[m[32m  vector<TileType> tts_new = map->get_secondary_terrain();[m
[32m+[m
[32m+[m[32m  EXPECT_EQ(2, tts_new.size());[m
[32m+[m
[32m+[m[32m  for (const auto tt : tts)[m
[32m+[m[32m  {[m
[32m+[m[32m    EXPECT_TRUE(std::find(tts_new.begin(), tts_new.end(), tt) != tts_new.end());[m
[32m+[m[32m  }[m
[32m+[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mTEST_F(SW_Engine_Map, get_secondary_terrain)[m
[32m+[m[32m{[m
[32m+[m[32m  MapPtr map = make_map();[m
[32m+[m
[32m+[m[32m  EXPECT_TRUE(map->get_secondary_terrain().empty());[m
[32m+[m
[32m+[m[32m  vector<TileType> ttv = { TileType::TILE_TYPE_SEA, TileType::TILE_TYPE_RIVER };[m
[32m+[m
[32m+[m[32m  ostringstream ss;[m
[32m+[m[32m  ss << static_cast<int>(TileType::TILE_TYPE_SEA) << "," << static_cast<int>(TileType::TILE_TYPE_RIVER);[m
[32m+[m[32m  map->set_property(MapProperties::MAP_PROPERTIES_SECONDARY_TERRAIN, ss.str());[m
[32m+[m
[32m+[m[32m  vector<TileType> sec_ter = map->get_secondary_terrain();[m
[32m+[m
[32m+[m[32m  EXPECT_FALSE(sec_ter.empty());[m
[32m+[m[32m  EXPECT_EQ(2, sec_ter.size());[m
[32m+[m[41m  [m
[32m+[m[32m  for (const auto tt : ttv)[m
[32m+[m[32m  {[m
[32m+[m[32m    EXPECT_TRUE(std::find(sec_ter.begin(), sec_ter.end(), tt) != sec_ter.end());[m
[32m+[m[32m  }[m
[32m+[m[32m}[m
\ No newline at end of file[m
[1mdiff --git a/suggestions.txt b/suggestions.txt[m
[1mindex a4c07533f..fc0b665c9 100644[m
[1m--- a/suggestions.txt[m
[1m+++ b/suggestions.txt[m
[36m@@ -1,5 +1,4 @@[m
 Me:[m
[31m-- Weird behaviour when character with same name already exists[m
 - NPCs run away when missile/spell/wand attacked and can't reach[m
 - spell arcana (bind to capitals in spell list)[m
 - sea creatures on sea tiles in other maps[m
[1mdiff --git a/world/include/Map.hpp b/world/include/Map.hpp[m
[1mindex ac016c7cc..7341d45b2 100644[m
[1m--- a/world/include/Map.hpp[m
[1m+++ b/world/include/Map.hpp[m
[36m@@ -168,6 +168,10 @@[m [mclass Map : public ISerializable[m
 [m
     Coordinate get_starting_location() const;[m
 [m
[32m+[m[32m    void set_secondary_terrain(const std::vector<TileType>& new_secondary_terrain);[m
[32m+[m[32m    void add_secondary_terrain(const TileType tt);[m
[32m+[m[32m    std::vector<TileType> get_secondary_terrain() const;[m
[32m+[m
     bool serialize(std::ostream& stream) const override;[m
     bool deserialize(std::istream& stream) override;[m
 [m
[1mdiff --git a/world/include/MapProperties.hpp b/world/include/MapProperties.hpp[m
[1mindex c3ec36029..6d59a199a 100644[m
[1m--- a/world/include/MapProperties.hpp[m
[1m+++ b/world/include/MapProperties.hpp[m
[36m@@ -111,6 +111,7 @@[m [mclass MapProperties[m
     static const std::string MAP_PROPERTIES_COASTLINE_SOUTH;[m
     static const std::string MAP_PROPERTIES_COASTLINE_EAST;[m
     static const std::string MAP_PROPERTIES_COASTLINE_WEST;[m
[32m+[m[32m    static const std::string MAP_PROPERTIES_SECONDARY_TERRAIN;[m
 [m
   protected:[m
     MapProperties();[m
[1mdiff --git a/world/source/Map.cpp b/world/source/Map.cpp[m
[1mindex 7fa6d0ed3..9c4e041d9 100644[m
[1m--- a/world/source/Map.cpp[m
[1m+++ b/world/source/Map.cpp[m
[36m@@ -865,6 +865,52 @@[m [mCoordinate Map::get_starting_location() const[m
   return c;[m
 }[m
 [m
[32m+[m[32mvoid Map::set_secondary_terrain(const vector<TileType>& new_secondary_terrain)[m
[32m+[m[32m{[m
[32m+[m[32m  ostringstream ss;[m
[32m+[m
[32m+[m[32m  for (size_t i = 0; i < new_secondary_terrain.size(); i++)[m
[32m+[m[32m  {[m
[32m+[m[32m    ss << static_cast<int>(new_secondary_terrain[i]);[m
[32m+[m
[32m+[m[32m    if (i < new_secondary_terrain.size() - 1)[m
[32m+[m[32m    {[m
[32m+[m[32m      ss << ",";[m
[32m+[m[32m    }[m
[32m+[m[32m  }[m
[32m+[m
[32m+[m[32m  set_property(MapProperties::MAP_PROPERTIES_SECONDARY_TERRAIN, ss.str());[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvoid Map::add_secondary_terrain(const TileType tt)[m
[32m+[m[32m{[m
[32m+[m[32m  vector<TileType> sec_ter = get_secondary_terrain();[m
[32m+[m
[32m+[m[32m  if (std::find(sec_ter.begin(), sec_ter.end(), tt) == sec_ter.end())[m
[32m+[m[32m  {[m
[32m+[m[32m    sec_ter.push_back(tt);[m
[32m+[m[32m    set_secondary_terrain(sec_ter);[m
[32m+[m[32m  }[m
[32m+[m[32m}[m
[32m+[m
[32m+[m[32mvector<TileType> Map::get_secondary_terrain() const[m
[32m+[m[32m{[m
[32m+[m[32m  vector<TileType> sec_ter;[m
[32m+[m
[32m+[m[32m  string sec_ter_s = get_property(MapProperties::MAP_PROPERTIES_SECONDARY_TERRAIN);[m
[32m+[m[32m  if (!sec_ter_s.empty())[m
[32m+[m[32m  {[m
[32m+[m[32m    vector<string> sec_ter_v = String::create_string_vector_from_csv_string(sec_ter_s);[m
[32m+[m
[32m+[m[32m    for (const auto& s : sec_ter_v)[m
[32m+[m[32m    {[m
[32m+[m[32m      sec_ter.push_back(static_cast<TileType>(String::to_int(s)));[m
[32m+[m[32m    }[m
[32m+[m[32m  }[m
[32m+[m
[32m+[m[32m  return sec_ter;[m
[32m+[m[32m}[m
[32m+[m
 bool Map::serialize(ostream& stream) const[m
 {[m
   // creatures - not serialized.  build up after deserialization.[m
[1mdiff --git a/world/source/MapProperties.cpp b/world/source/MapProperties.cpp[m
[1mindex 5c72ad67d..88fcd97a7 100644[m
[1m--- a/world/source/MapProperties.cpp[m
[1m+++ b/world/source/MapProperties.cpp[m
[36m@@ -43,3 +43,4 @@[m [mconst string MapProperties::MAP_PROPERTIES_COASTLINE_NORTH = "MAP_PROPERTIES_COA[m
 const string MapProperties::MAP_PROPERTIES_COASTLINE_SOUTH = "MAP_PROPERTIES_COASTLINE_SOUTH";[m
 const string MapProperties::MAP_PROPERTIES_COASTLINE_EAST = "MAP_PROPERTIES_COASTLINE_EAST";[m
 const string MapProperties::MAP_PROPERTIES_COASTLINE_WEST = "MAP_PROPERTIES_COASTLINE_WEST";[m
[32m+[m[32mconst string MapProperties::MAP_PROPERTIES_SECONDARY_TERRAIN = "MAP_PROPERTIES_SECONDARY_TERRAIN";[m
