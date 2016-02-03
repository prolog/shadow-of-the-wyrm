#pragma once
#include "Generator.hpp"

class SeaGenerator : public SOTW::Generator
{
  public:
    SeaGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;
};
