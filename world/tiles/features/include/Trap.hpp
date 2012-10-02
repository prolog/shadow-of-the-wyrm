#pragma once
#include <boost/shared_ptr.hpp>

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class Trap
{
  public:
    Trap();
    virtual ~Trap() {};

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};

typedef boost::shared_ptr<Trap> TrapPtr;
