#pragma once
#include "IFeatureManipulator.hpp"
#include "Feature.hpp"

class WheelAndLoomManipulator : public IFeatureManipulator
{
  public:
    WheelAndLoomManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;

  protected:
    void add_no_weaving_skill_message(CreaturePtr creature);
    void add_no_fibres_message(CreaturePtr creature);
    void add_successful_weaving_message(CreaturePtr creature);

    ItemPtr create_woven_armour(CreaturePtr creature, ItemPtr fibre, const EquipmentWornLocation worn_loc);

    std::map<EquipmentWornLocation, std::string> loom_map;
};

