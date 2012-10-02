#pragma once
#include "Trap.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class ITrappable
{
  public:
    // Implemented by whatever object has the trappable interface - 
    // features, tiles, etc.
    virtual TrapPtr get_trap() = 0;

  protected:
    ITrappable();
    ~ITrappable();

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};
