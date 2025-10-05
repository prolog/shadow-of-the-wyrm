#pragma once
#include "DefaultFeatureManipulator.hpp"
#include "Feature.hpp"

class HiveManipulator : public DefaultFeatureManipulator
{
  public:
    HiveManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;

  protected:
    bool shake_hive(TilePtr tile, FeaturePtr feature, CreaturePtr creature, const std::string& message_sid);
};

