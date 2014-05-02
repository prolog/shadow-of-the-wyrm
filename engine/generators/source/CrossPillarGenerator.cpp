#include "CrossPillarGenerator.hpp"
#include "TileGenerator.hpp"

using namespace std;

int CrossPillarGenerator::get_height() const
{
  return 3;
}

int CrossPillarGenerator::get_width() const
{
  return 3;
}

void CrossPillarGenerator::generate(MapPtr map, const int y_topleft, const int x_topleft)
{
  vector<Coordinate> pillar_points({{y_topleft, x_topleft+1},
                                    {y_topleft+1, x_topleft+1},
                                    {y_topleft+2, x_topleft+1},
                                    {y_topleft+1, x_topleft},
                                    {y_topleft+1, x_topleft+2}});

  TileGenerator tg;
  TilePtr pillar_tile;  
  
  for (const Coordinate& c : pillar_points)
  {
    pillar_tile = tg.generate(TILE_TYPE_ROCK);
    map->insert(c.first, c.second, pillar_tile);
  }
}

#ifdef UNIT_TESTS
#include "unit_tests/CrossPillarGenerator_test.cpp"
#endif