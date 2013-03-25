#include "MapDisplayArea.hpp"

MapDisplayArea::MapDisplayArea()
: height(0), width(0)
{
}

MapDisplayArea::MapDisplayArea(const uint new_height, const uint new_width)
: height(new_height), width(new_width)
{
}

void MapDisplayArea::set_height(const uint new_height)
{
  height = new_height;
}

uint MapDisplayArea::get_height() const
{
  return height;
}

void MapDisplayArea::set_width(const uint new_width)
{
  width = new_width;
}

uint MapDisplayArea::get_width() const
{
  return width;
}

#ifdef UNIT_TESTS
#include "unit_tests/MapDisplayArea_test.cpp"
#endif
