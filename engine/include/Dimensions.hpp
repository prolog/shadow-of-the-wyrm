#pragma once

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

  protected:
    int y;
    int x;
};
