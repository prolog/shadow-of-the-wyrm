#pragma once

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

// An interface class that allows the player to "h"andle a particular
// feature.  Handling a door opens/shuts/unlocks it as appropriate.
// Handling a throne while on the square causes the player to sit.  etc.
class IHandleable
{
  public:
    IHandleable() {};
    virtual ~IHandleable() {};

    virtual bool handle() = 0;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};
