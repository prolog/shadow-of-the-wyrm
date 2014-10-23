#pragma once
#include "Generator.hpp"
#include "Map.hpp"
#include "Room.hpp"
#include "TileGenerator.hpp"

class DungeonGenerator : public SL::Generator
{
  public:
    DungeonGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

    virtual bool can_create_initial_items() const override;

  protected:

    virtual bool get_permanence_default() const override;
    
    virtual MapType get_map_type() const override;
    virtual bool    generate_dungeon(MapPtr map);
    virtual TilePtr generate_tile(MapPtr current_map, int row, int col);

    // Corridor and room placement routines.  True if the attempt succeeded, false otherwise.
    virtual bool    check_range(MapPtr map, int start_row, int start_col, int size_rows, int size_cols);
    virtual bool    generate_and_place_room(MapPtr map, int& start_y, int& start_x, int& height, int& width);
    virtual bool    place_room(MapPtr map, int start_row, int start_col, int size_rows, int size_cols);
    virtual bool    place_doorway(MapPtr map, int row, int col);
    virtual bool    place_doorways(MapPtr current_map);
    virtual bool    place_staircases(MapPtr current_map);
    virtual bool    potentially_generate_room_features(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col);

    bool connect_rooms(MapPtr map, const Room& room1, const Room& room2);
    bool is_tile_adjacent_to_room_tile(const Dimensions& dim, const int row, const int col);
    bool tile_exists_outside_of_room(const int row, const int col, const bool check_connected, const bool check_unconnected);
    
    void initialize_and_seed_cheat_vectors(const Dimensions& dim);

    const int DEFAULT_MIN_HEIGHT;
    const int DEFAULT_MAX_HEIGHT;
    const int DEFAULT_MIN_WIDTH;
    const int DEFAULT_MAX_WIDTH;
    const int MIN_NUM_ROOMS;
    const int MAX_NUM_ROOMS;

    TileGenerator tg;

    std::vector<Room> unconnected_rooms;
    std::vector<Room> connected_rooms;
    
    // These are used to cheat the otherwise uniformly random approach:
    // By seeding them with some values, dungeons are generated that still
    // look random, but have a distribution of rooms across the entire grid
    // (mostly).
    std::vector<int> y1_cheaty_vector;
    std::vector<int> y2_cheaty_vector;    
};
