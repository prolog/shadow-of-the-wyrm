#pragma once
#include "Feature.hpp"
#include "StatueTypes.hpp"

// There are two types of statues: generic statues, which are purely
// decorative, exist only for flavour, and have no in-game effect; and
// regular statues, which can be transmogrified into a particular creature
// type.  FIXME: Only the former is currently implemented.
class StatueGenerator
{
  public:
    static FeaturePtr generate_decorative_statue(const DecorativeStatueType statue_type);

  protected:
    StatueGenerator();
};
