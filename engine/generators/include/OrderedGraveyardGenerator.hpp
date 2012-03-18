#pragma once
#include "GraveyardGenerator.hpp"

class OrderedGraveyardGenerator : public GraveyardGenerator
{
  public:
    OrderedGraveyardGenerator(const std::string& new_map_exit_id);

  protected:
    virtual void add_graves(MapPtr map);
};
