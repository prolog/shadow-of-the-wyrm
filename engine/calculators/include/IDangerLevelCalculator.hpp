#pragma once
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include "common.hpp"
#include "Map.hpp"

// Danger level calculator.  Different types of map (world, overworld,
// underworld) have different methods of danger calculation, so this class
// provides a common interface that abstracts away the details.
class IDangerLevelCalculator
{
  public:
    // Calculate the new danger level, given the old.
    virtual uint calculate(MapPtr old_map, MapPtr new_map = boost::shared_ptr<Map>()) const = 0;
    virtual ~IDangerLevelCalculator() {};
};

typedef boost::shared_ptr<IDangerLevelCalculator> IDangerLevelCalculatorPtr;

