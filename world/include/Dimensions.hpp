#pragma once
#include "Depth.hpp"

#define DEFAULT_DIMENSIONS_Y 20;
#define DEFAULT_DIMENSIONS_X 80;

class Dimensions
{
  public:
    Dimensions();
    Dimensions(const int new_x, const int new_y);

    void set_y(int new_y);
    int  get_y() const;

    void set_x(int new_x);
    int  get_x() const;

    void set_depth(const Depth& new_depth);
    Depth depth() const;

  protected:
    int y;
    int x;
    Depth dim_depth;
};

