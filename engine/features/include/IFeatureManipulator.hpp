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
    IFeatureManipulator(FeaturePtr new_feature) : feature(new_feature) {};

    // Kicking returns void because kicking something and getting to the point
    // of using a manipulator is always an action.  
    virtual void kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature) = 0;
    
    // Handling a feature can affect the tile on which the feature is present,
    // so include that as a parameter.  Include the creature so that if a message
    // is added (e.g., "You pour yourself a drink!" or "The goblin pours himself
    // a drink!"), the correct message can be added based on the creature, and
    // whether the creature is the player or not.
    virtual bool handle(TilePtr tile, CreaturePtr creature) = 0;

  protected:
    FeaturePtr feature;
};

typedef std::shared_ptr<IFeatureManipulator> IFeatureManipulatorPtr;
