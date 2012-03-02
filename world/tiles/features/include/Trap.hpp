#pragma once
#include <boost/shared_ptr.hpp>

class Trap
{
  public:
    Trap();

  protected:
};

typedef boost::shared_ptr<Trap> TrapPtr;
