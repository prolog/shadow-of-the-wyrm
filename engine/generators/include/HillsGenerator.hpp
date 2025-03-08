#pragma once
#include "Generator.hpp"

class HillsGenerator : public SOTW::Generator
{
  public:
    HillsGenerator(const std::string& map_exit_id);
    virtual ~HillsGenerator() = default;

    MapPtr generate(const Dimensions& dim) override;
};
