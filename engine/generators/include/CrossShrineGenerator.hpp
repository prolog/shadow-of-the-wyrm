#pragma once
#include "Generator.hpp"
#include "TileGenerator.hpp"

class CrossShrineGenerator : public SOTW::Generator
{
  public:
    CrossShrineGenerator(MapPtr base_map);

    virtual MapPtr generate(const Dimensions& dim) override;
    virtual MapPtr generate();

  protected:
    MapPtr base_map;
    TileGenerator tg;
};

