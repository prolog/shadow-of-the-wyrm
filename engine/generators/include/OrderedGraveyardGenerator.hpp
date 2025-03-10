#pragma once
#include "GraveyardGenerator.hpp"

class OrderedGraveyardGenerator : public GraveyardGenerator
{
  public:
    OrderedGraveyardGenerator(const std::string& new_map_exit_id);
    virtual ~OrderedGraveyardGenerator() = default;

    virtual void add_graves(MapPtr map) override;
    virtual void add_graves(MapPtr map, const int start_row, const int end_row, const int start_col, const int end_col) override;
};
