#pragma once
#include "GraveyardGenerator.hpp"

class ScatteredGraveyardGenerator : public GraveyardGenerator
{
  public:
    ScatteredGraveyardGenerator(const std::string& new_map_exit_id);

  protected:
    virtual void add_graves(MapPtr map);
};
