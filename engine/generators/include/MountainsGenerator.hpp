#pragma once
#include "Generator.hpp"

class MountainsGenerator : public Generator
{
  public:
    MountainsGenerator(const std::string& map_exit_id);

    MapPtr generate(const Dimensions& dim);
};
