#pragma once
#include "DoorState.hpp"
#include "Feature.hpp"
#include "ILockable.hpp"

// Doors are Features, but like Windows, will be re-used outside the
// dungeon environment.
class Door : public Feature, public ILockable
{
  public:
    Door(LockPtr new_lock, const DoorState& new_state);

    void set_lock(LockPtr new_lock);
    LockPtr get_lock();

    void set_state(const DoorState& new_state);
    DoorState get_state();

  protected:
    LockPtr lock;
    DoorState state;
};
