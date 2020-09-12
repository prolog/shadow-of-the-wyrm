#pragma once
#include "SectorFeature.hpp"

class GardenSectorFeature : public SectorFeature
{
  public:
    GardenSectorFeature(const std::string& deity_id = "", const AlignmentRange ar = AlignmentRange::ALIGNMENT_RANGE_NEUTRAL);

    virtual bool generate_feature(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) override;

    std::string get_deity_id() const;
    bool has_altar() const;
    AlignmentRange get_alignment_range() const;

  protected:
    virtual bool generate_garden(MapPtr map, const Coordinate& start_coord, const Coordinate& end_coord) = 0;

    std::string deity_id;
    AlignmentRange alignment_range;
};

