#include "Entrance.hpp"
#include "MaterialFactory.hpp"

Entrance::Entrance(LockPtr new_lock, const EntranceState& new_state)
: Feature(MaterialFactory::create_material(MATERIAL_TYPE_WOOD)), lock(new_lock), state(new_state)
{
}

void Entrance::set_lock(LockPtr new_lock)
{
  lock = new_lock;
}

LockPtr Entrance::get_lock()
{
  return lock;
}

void Entrance::set_state(const EntranceState& new_state)
{
  state = new_state;
}

EntranceState Entrance::get_state() const
{
  return state;
}

void Entrance::set_maximum_size(const CreatureSize new_size)
{
  maximum_size = new_size;
}

CreatureSize Entrance::get_maximum_size() const
{
  return maximum_size;
}

void Entrance::set_trap(TrapPtr new_trap)
{
  trap = new_trap;
}

TrapPtr Entrance::get_trap()
{
  return trap;
}
