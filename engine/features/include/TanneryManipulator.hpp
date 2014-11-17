#pragma once
#include "IFeatureManipulator.hpp"
#include "Feature.hpp"

class TanneryManipulator : public IFeatureManipulator
{
  public:
    TanneryManipulator(FeaturePtr feature);

    void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) override;
    bool handle(TilePtr tile, CreaturePtr creature) override;

  protected:
    void add_no_skins_message(CreaturePtr creature);
};

