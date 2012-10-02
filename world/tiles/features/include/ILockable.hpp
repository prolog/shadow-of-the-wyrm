#include "Lock.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

class ILockable
{
  public:
    ILockable();
    ~ILockable();

    virtual LockPtr get_lock() = 0;

  private:
    friend class boost::serialization::access;

    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
    }
};
