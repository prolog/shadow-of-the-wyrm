#pragma once
#include "ActionManager.hpp"
#include "FeatureManipulator.hpp"
#include "Feature.hpp"

class SlotMachineManipulator : public FeatureManipulator
{
  public:
    SlotMachineManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item) override;

  protected:
    void initialize();

    static std::vector<std::string> slot_faces;
};

