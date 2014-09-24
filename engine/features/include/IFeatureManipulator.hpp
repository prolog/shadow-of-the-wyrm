#pragma once
#include <memory>
#include "Creature.hpp"
#include "Map.hpp"

// Interface class that allows the engine to manipulate the tile features.
// Each class that implements this interface allows the engine to 
// manipulate a particular feature.  E.g., an altar, a door, etc.
class IFeatureManipulator
{
  public:
    virtual void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) = 0;
};

typedef std::shared_ptr<IFeatureManipulator> IFeatureManipulatorPtr;
