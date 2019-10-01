#pragma once
#include <memory>

class SDLCursorLocation
{
  public:
    SDLCursorLocation(const int new_total_rows, const int new_total_cols);

    bool incr();
    bool decr();
    void reset();

    void set_yx(const int new_y, const int new_x);

    void set_y(const int new_y);
    int get_y() const;

    void set_x(const int new_x);
    int get_x() const;

    std::pair<int, int> get_yx() const;

  protected:
    int y;
    int x;
    const int total_rows, total_cols;
};
