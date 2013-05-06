#pragma once
#include "Generator.hpp"

class HillsGenerator : public SL::Generator
{
  public:
    HillsGenerator(const std::string& map_exit_id);

    MapPtr generate(const Dimensions& dim);
};
