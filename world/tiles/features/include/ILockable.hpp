#include "Lock.hpp"

class ILockable
{
  public:
    virtual LockPtr get_lock() = 0;

  protected:
    ILockable();
    ~ILockable();
};
