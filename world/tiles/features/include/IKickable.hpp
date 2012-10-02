#pragma once

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

// An interface class that denotes that whatever it's attached to
// responds to kicking in some way.
class IKickable
{
  public:
    IKickable() {};
    virtual ~IKickable() {};

    virtual bool kick() = 0;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};
