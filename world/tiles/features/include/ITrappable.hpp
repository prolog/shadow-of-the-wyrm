#pragma once
#include "Trap.hpp"

class ITrappable
{
  public:
    // Implemented by whatever object has the trappable interface - 
    // features, tiles, etc.
    virtual TrapPtr get_trap() = 0;

  protected:
    ITrappable();
    ~ITrappable();
};
