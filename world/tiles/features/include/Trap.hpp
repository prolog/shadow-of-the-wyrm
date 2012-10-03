#pragma once
#include <boost/shared_ptr.hpp>

class Trap
{
  public:
    Trap();
    virtual ~Trap() {};
};

typedef boost::shared_ptr<Trap> TrapPtr;
