#include "SectorFeature.hpp"

class HouseSectorFeature : public SectorFeature
{
  public:
    HouseSectorFeature();
    HouseSectorFeature(const bool ruined);

  protected:
    bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord);

    int growth_rate;
};
