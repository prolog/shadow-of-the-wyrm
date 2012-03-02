#include "Door.hpp"

Door::Door(LockPtr new_lock, const DoorState& new_state)
: lock(new_lock), state(new_state)
{
}

void Door::set_lock(LockPtr new_lock)
{
  lock = new_lock;
}

LockPtr Door::get_lock()
{
  return lock;
}

void Door::set_state(const DoorState& new_state)
{
  state = new_state;
}

DoorState Door::get_state()
{
  return state;
}
