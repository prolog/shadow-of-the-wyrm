#pragma once
#include "Generator.hpp"
#include "Map.hpp"
#include "MapUtils.hpp"

class CavernGenerator : public SOTW::Generator
{
  public:
    CavernGenerator(const std::string& map_exit_id);
    virtual ~CavernGenerator() = default;
    
    virtual MapPtr generate(const Dimensions& dimensions) override;

    virtual bool can_create_initial_items() const override;
    virtual bool get_allow_ancient_beasts() const;

  protected:
    virtual bool get_permanence_default() const override;
    virtual MapType get_map_type() const override;

    void generate_cavern(MapPtr map);
    void generate_traps(MapPtr map);
    MapComponents get_cavern_components(MapPtr map);
    void connect_cavern_components(MapPtr map, const MapComponents& cc);
    void connect_caverns(MapPtr map, const Coordinate& first, const Coordinate& second);
    void reset_cavern_edges(MapPtr map);
    void generate_staircases(MapPtr map);
    void generate_staircase(MapPtr map, const TileType tile_type, const Direction direction);

    static int MIN_NUM_TRAPS;
    static int MAX_NUM_TRAPS;
};
