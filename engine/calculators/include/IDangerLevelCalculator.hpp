#pragma once
#include <memory>
#include "common.hpp"
#include "Map.hpp"

// Danger level calculator.  Different types of map (world, overworld,
// underworld) have different methods of danger calculation, so this class
// provides a common interface that abstracts away the details.
class IDangerLevelCalculator
{
  public:
    // Calculate the new danger level, given the old.
    virtual int calculate(MapPtr old_map, MapPtr new_map = std::shared_ptr<Map>()) const = 0;
    virtual ~IDangerLevelCalculator() {};
};

typedef std::shared_ptr<IDangerLevelCalculator> IDangerLevelCalculatorPtr;

