#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class SewerGenerator : public SOTW::Generator
{
  public:
    SewerGenerator(const std::string& map_exit_id);
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    TileGenerator tg;
};
