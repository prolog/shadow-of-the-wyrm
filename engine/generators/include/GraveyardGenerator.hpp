#pragma once
#include "Generator.hpp"
#include "GraveInscriptionGenerator.hpp"
#include "TileGenerator.hpp"

class GraveyardGenerator : public SOTW::Generator
{
  public:
    GraveyardGenerator(const std::string& new_map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

    // This is the function that determines whether a graveyard is ordered or scattered, and
    // must be implemented by each subclass.
    virtual void add_graves(MapPtr map) = 0;
    virtual void add_graves(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) = 0;

  protected:
    virtual bool get_permanence_default() const override;
    virtual void add_inscription(TilePtr grave_tile);

    virtual TilePtr generate_tile(MapPtr current_map, const int row, const int col);
    
    virtual void add_tomb_if_necessary(MapPtr map);
    virtual void add_tomb(MapPtr map);
    virtual void add_framing_trees(MapPtr map);
    virtual void add_random_foliage(MapPtr map);
    
    const int TOMB_MIN_SIZE;
    const int TOMB_MAX_SIZE;
    const int PCT_CHANCE_INSCRIPTION;

    TileGenerator tg;
    GraveInscriptionGenerator gig;
};
