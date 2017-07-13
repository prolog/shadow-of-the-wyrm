#pragma once
#include "Generator.hpp"

class VoidGenerator : public SOTW::Generator
{
  public:
    VoidGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;
};
