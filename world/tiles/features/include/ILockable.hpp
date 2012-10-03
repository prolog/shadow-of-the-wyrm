#include "Lock.hpp"

class ILockable
{
  public:
    ILockable();
    ~ILockable();

    virtual LockPtr get_lock() = 0;
};
