#pragma once
#include "CastleGeneratorStrategy.hpp"

class MotteBaileyCastleGeneratorStrategy : public CastleGeneratorStrategy
{
  public:
    void generate(MapPtr castle_map);

  protected:
    void generate_moat(MapPtr castle_map, const int moat_radius);
    void generate_motte(MapPtr castle_map, const int motte_height, const int motte_width);

    static const int MIN_MOTTE_WIDTH;
    static const int MIN_MOTTE_HEIGHT;
};

