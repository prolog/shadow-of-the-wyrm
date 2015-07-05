#pragma once
#include "AlignmentEnums.hpp"
#include "Door.hpp"
#include "Feature.hpp"
#include "Sarcophagus.hpp"

enum struct PewDirection
{
  PEW_DIRECTION_NORTH_SOUTH = 0,
  PEW_DIRECTION_EAST_WEST = 1
};

class FeatureGenerator
{
  public:
    static FeaturePtr generate_altar(const std::string& deity_id, const AlignmentRange range);
    static FeaturePtr generate_bed();
    static DoorPtr generate_door();
    static FeaturePtr generate_gate();
    static FeaturePtr generate_fire_pillar();
    static FeaturePtr generate_forge();
    static FeaturePtr generate_fountain();
    static FeaturePtr generate_pew(const PewDirection pew_direction = PewDirection::PEW_DIRECTION_NORTH_SOUTH);
    static FeaturePtr generate_bench();
    static SarcophagusPtr generate_sarcophagus(const MaterialType material_type = MaterialType::MATERIAL_TYPE_STONE);
    static FeaturePtr generate_tannery();
    static FeaturePtr generate_jeweler_workbench();
    static FeaturePtr generate_wheel_and_loom();
    static FeaturePtr generate_stone_marker();

  protected:
    FeatureGenerator();
    ~FeatureGenerator();
};
