#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class GraveyardGenerator : public SL::Generator
{
  public:
    GraveyardGenerator(const std::string& new_map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual bool get_permanence_default() const override;

    virtual TilePtr generate_tile(MapPtr current_map, const int row, const int col);

    // This is the function that determines whether a graveyard is ordered or scattered, and
    // must be implemented by each subclass.
    virtual void add_graves(MapPtr map) = 0;
    
    virtual void add_tomb_if_necessary(MapPtr map);
    virtual void add_tomb(MapPtr map);
    virtual void add_framing_trees(MapPtr map);
    virtual void add_random_foliage(MapPtr map);
    
    const int TOMB_MIN_SIZE;
    const int TOMB_MAX_SIZE;

    TileGenerator tg;
};
