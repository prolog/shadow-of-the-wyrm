#pragma once
#include <boost/shared_ptr.hpp>

// A class for querying whether certain things should be done, given the
// type of map.
class IMapTypeQuery
{
  public:
    virtual bool should_update_depth() const = 0;
    virtual ~IMapTypeQuery() {};
};

typedef boost::shared_ptr<IMapTypeQuery> IMapTypeQueryPtr;

