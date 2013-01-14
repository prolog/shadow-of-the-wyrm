#pragma once
#include "AlignmentEnums.hpp"
#include "Door.hpp"
#include "Feature.hpp"

enum PewDirection
{
  PEW_DIRECTION_NORTH_SOUTH = 0,
  PEW_DIRECTION_EAST_WEST = 1
};

class FeatureGenerator
{
  public:
    static FeaturePtr generate_altar(const std::string& deity_id, const AlignmentRange range);
    static DoorPtr generate_door();
    static FeaturePtr generate_gate();
    static FeaturePtr generate_fire_pillar();
    static FeaturePtr generate_fountain();
    static FeaturePtr generate_pew(const PewDirection pew_direction = PEW_DIRECTION_NORTH_SOUTH);
    static FeaturePtr generate_bench();

  protected:
    FeatureGenerator();
    ~FeatureGenerator();
};
