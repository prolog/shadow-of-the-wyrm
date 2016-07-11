#pragma once
#include "Game.hpp"
#include "Map.hpp"
#include "MessageManagerFactory.hpp"

// Class responsible for generating creatures (either a pre-set list, or a list
// built up based on danger level/terrain type/etc) on to a given map.
class MapCreatureGenerator
{
  public:
    // Generate the creatures.  Returns true if creatures were created (with
    // max danger level), false otherwise.
    virtual std::tuple<bool, int, Rarity> generate_creatures(MapPtr map, const int danger_level, const std::map<std::string, std::string>& additional_properties);
    virtual std::tuple<bool, int, Rarity> generate_initial_set_creatures(MapPtr map, const std::map<std::string, std::string>& additional_properties);
    virtual std::tuple<bool, int, Rarity> generate_random_creatures(MapPtr map, const int danger_level, const std::map<std::string, std::string>& additional_properties);

  protected:
    void add_creature_to_map_and_potentially_notify(Game& game, CreaturePtr creature, MapPtr map, IMessageManager& manager, const int danger_level, const int creature_row, const int creature_col, unsigned int& current_creatures_placed, std::tuple<bool, int, Rarity>& creatures_generated, bool& out_of_depth_msg_added);
    int get_num_creatures(MapPtr map, const int max_creatures);
    int get_danger_level(MapPtr map, const int base_danger_level);
    Coordinate get_coordinate_for_creature(MapPtr map, CreaturePtr generated_creature, const int rows, const int cols);

    static const int OUT_OF_DEPTH_CREATURES_CHANCE;
};

