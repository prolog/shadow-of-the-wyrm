#pragma once
#include "Generator.hpp"

class MountainsGenerator : public Generator
{
  public:
    MapPtr generate(const Dimensions& dim, const std::string& map_exit_id);
};
