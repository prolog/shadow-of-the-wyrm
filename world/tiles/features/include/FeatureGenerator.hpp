#pragma once
#include "AlignmentEnums.hpp"
#include "StatueTypes.hpp"
#include "Features.hpp"

enum struct PewDirection
{
  PEW_DIRECTION_NORTH_SOUTH = 0,
  PEW_DIRECTION_EAST_WEST = 1
};

using FeatureSerializationMap = std::map<ClassIdentifier, FeaturePtr>;

class FeatureGenerator
{
  public:
    static FeaturePtr create_feature(const ClassIdentifier ci);
    static LockPtr create_lock();
    static TrapPtr create_trap();
    static FeaturePtr generate_altar(const std::string& deity_id, const AlignmentRange range);
    static FeaturePtr generate_barrel();
    static FeaturePtr generate_bed();
    static DoorPtr generate_door(const EntranceStateType et = EntranceStateType::ENTRANCE_TYPE_OPEN);
    static FeaturePtr generate_gate();
    static FeaturePtr generate_fire_pillar();
    static FeaturePtr generate_forge();
    static FeaturePtr generate_kiln();
    static FeaturePtr generate_fountain();
    static FeaturePtr generate_pew(const PewDirection pew_direction = PewDirection::PEW_DIRECTION_NORTH_SOUTH);
    static FeaturePtr generate_bench();
    static SarcophagusPtr generate_sarcophagus(const MaterialType material_type = MaterialType::MATERIAL_TYPE_STONE);
    static SlotMachinePtr generate_slot_machine(const MaterialType material_type, const int cost, const int pct_chance_win, const float payout_multiplier);
    static FeaturePtr generate_tannery();
    static FeaturePtr generate_pulper();
    static FeaturePtr generate_jeweler_workbench();
    static FeaturePtr generate_wheel_and_loom();
    static FeaturePtr generate_stone_marker();
    static FeaturePtr generate_table();
    static FeaturePtr generate_configurable_feature(const std::string& configurable_feature_id);
    static FeaturePtr generate_configurable_feature(const MaterialType mt, const Symbol& symbol, const std::string& desc_sid);
    static FeaturePtr generate_sign(const std::string& text_sid);
    static FeaturePtr generate_decorative_statue(const DecorativeStatueType statue_type);
    static PetrifiedCorpseStatuePtr generate_petrified_corpse_statue(const std::string& corpse_description_sid);

    static void set_feature_symbol_map(const FeatureSymbolMap& fsm);
    static FeatureSymbolMap get_feature_symbol_map();

  protected:
    static Symbol get_config_symbol(const ClassIdentifier ci);
    static void initialize_feature_map();

    FeatureGenerator();
    ~FeatureGenerator();

    static FeatureSymbolMap feature_symbol_map;
    static FeatureSerializationMap feature_map;
};

