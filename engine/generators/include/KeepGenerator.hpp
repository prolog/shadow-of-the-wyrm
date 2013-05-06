#pragma once
#include "Generator.hpp"

class KeepGenerator : public SL::Generator
{
  public:
    KeepGenerator(MapPtr new_base_map, const int chance_decay = 0);

    virtual MapPtr generate(const Dimensions& dim);
    virtual MapPtr generate();

  protected:
    virtual bool get_permanence_default() const;

    virtual void create_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    virtual void populate_keep(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    virtual void create_entrance(MapPtr map, const int start_row, const int start_col, const int height, const int width);
    
    MapPtr base_map;
    const int PCT_CHANCE_DECAY;
};
