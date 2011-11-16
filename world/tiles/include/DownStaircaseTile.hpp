#pragma once
#include "StaircaseTile.hpp"
#include <boost/shared_ptr.hpp>

class DownStaircaseTile : public StaircaseTile
{
  public:
    StaircaseType get_staircase_type() const;
};

typedef boost::shared_ptr<DownStaircaseTile> DownStaircaseTilePtr;
