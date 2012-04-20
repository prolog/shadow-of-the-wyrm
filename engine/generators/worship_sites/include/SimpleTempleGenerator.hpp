#pragma once
#include "ChurchGenerator.hpp"

// The Trickster's followers create simple, unadorned open-air temples, some
// barely smaller than roadside shrines.
class SimpleTempleGenerator : public ChurchGenerator
{
  public:
    SimpleTempleGenerator(const std::string& new_deity_id, MapPtr base_map);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim);

  protected:
    virtual void generate_temple(MapPtr map);
    virtual void generate_temple_features(MapPtr map, const int dais_start_row, const int dais_start_col, const int dais_size);    
};
