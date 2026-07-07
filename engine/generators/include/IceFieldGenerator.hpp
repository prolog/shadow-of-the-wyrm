#pragma once
#include "Generator.hpp"

class IceFieldGenerator : public SOTW::Generator
{
  public:
    IceFieldGenerator(const std::string& map_exit_id);
    virtual ~IceFieldGenerator() = default;
    
    virtual MapPtr generate(const Dimensions& dim) override;
};
