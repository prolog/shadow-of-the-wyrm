#pragma once
#include "Generator.hpp"

class FloatingTowerGenerator : public SOTW::Generator
{
  public:
    FloatingTowerGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;
};
