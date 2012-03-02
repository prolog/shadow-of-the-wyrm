#pragma once
#include "Generator.hpp"

class SeaGenerator : public Generator
{
  public:
    virtual MapPtr generate(const Dimensions& dim, const std::string& map_exit_id);
};
