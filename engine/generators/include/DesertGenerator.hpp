#pragma once
#include "Generator.hpp"

class DesertGenerator : public SL::Generator
{
  public:
    DesertGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim);
};
