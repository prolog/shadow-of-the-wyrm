#pragma once
#include "CastleGeneratorStrategy.hpp"

class MotteBaileyCastleGeneratorStrategy : public CastleGeneratorStrategy
{
  public:
    void generate(MapPtr castle_map);
    virtual ~MotteBaileyCastleGeneratorStrategy() = default;

  protected:
    void generate_moat(MapPtr castle_map, const int start_y, const int start_x, const int end_y, const int end_x);
    void generate_motte(MapPtr castle_map, const int motte_height, const int motte_width);
    void generate_bridge(MapPtr castle_map, const int start_y, const int start_x, const int end_y, const int end_x);

    static const int MIN_MOTTE_WIDTH;
    static const int MIN_MOTTE_HEIGHT;
};

