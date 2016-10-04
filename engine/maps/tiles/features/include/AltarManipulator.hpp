#pragma once
#include "IFeatureManipulator.hpp"

// Interface that defines a common handle() method for all altars.
class AltarManipulator : public IFeatureManipulator
{
  public:
    AltarManipulator(FeaturePtr feature);

    bool handle(TilePtr tile, CreaturePtr creature) override;
    bool drop(CreaturePtr dropping_creature, ItemPtr item) override;
};

