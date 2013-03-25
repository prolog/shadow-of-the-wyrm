#pragma once
#include "common.hpp"

class MapDisplayArea
{
  public:
    MapDisplayArea();
    MapDisplayArea(const uint height, const uint width);

    void set_height(const uint height);
    uint get_height() const;

    void set_width(const uint width);
    uint get_width() const;

  protected:
    uint height;
    uint width;
};
