#pragma once

// Any class that implements this interface can be used to offer
// things to the deities of the world.
class IOfferable
{
  public:
    virtual bool offer() = 0;
};
