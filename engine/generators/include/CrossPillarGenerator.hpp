#include "IPillarGenerator.hpp"

// Pillar generator that creates a pillar like:
//
// .#.
// ###
// .#.
class CrossPillarGenerator : public IPillarGenerator
{
  public:
    virtual int get_height() const override;
    virtual int get_width() const override;

    virtual void generate(MapPtr map, const int y_topleft, const int x_topleft);
};

