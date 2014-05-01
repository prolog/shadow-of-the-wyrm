#include "IPillarGenerator.hpp"

// A generator to create a "square pillar" of rock, like so:
// 
// ..##..
// ..##..
class SquarePillarGenerator : public IPillarGenerator
{
  public:
    virtual int get_height() const override;
    virtual int get_width() const override;

    virtual void generate(MapPtr map, const int y_topleft, const int x_topleft);
};

