#pragma once
#include <boost/shared_ptr.hpp>
#include "ITrappable.hpp"

// An abstract base class representing a dungeon feature.  A feature is
// like an item, but cannot move.  Examples include fireplaces, thrones,
// bookshelves, levers, etc.
//
// Features can be trapped.
class Feature : public ITrappable
{
  public:
    Feature();

    // If a feature is blocking, the square it occupies cannot be
    // occupied by another creature, and any items thrown, kicked, etc.,
    // in its direction will stop before reaching the tile.
    virtual bool get_blocking() = 0;

    // JCD FIXME fill in the rest later.

  protected:
};

typedef boost::shared_ptr<Feature> FeaturePtr;
