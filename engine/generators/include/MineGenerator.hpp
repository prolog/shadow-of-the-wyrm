#pragma once
#include "Generator.hpp"
#include "Room.hpp"

class MineGenerator : public SL::Generator
{
  public:
    MineGenerator(const std::string& map_exit_id);

    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual MapType get_map_type() const override;

    void generate_main_mining_corridor(MapPtr result_map);
    void dig_floor(MapPtr map, const std::vector<Coordinate>& tiles_to_dig);
    void generate_rooms(MapPtr result_map);
    void connect_rooms(MapPtr result_map);
    // Returns true if the room was able to be generated.
    bool generate_room(MapPtr map, const int start_y, const int start_x, const int height, const int width);

    void place_staircases(MapPtr map);
    bool get_permanence_default() const override;

    static const int MINE_MIN_ROOM_WIDTH;
    static const int MINE_MAX_ROOM_WIDTH;
    static const int MINE_MIN_ROOM_HEIGHT;
    static const int MINE_MAX_ROOM_HEIGHT;

    std::vector<Room> rooms;
    std::shared_ptr<Room> main_hallway_centre;
};

