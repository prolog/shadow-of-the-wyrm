#pragma once

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

// Any class that implements this interface can be used to offer
// things to the deities of the world.
class IOfferable
{
  public:
    IOfferable() {};
    virtual ~IOfferable() {};

    virtual bool offer() = 0;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};
