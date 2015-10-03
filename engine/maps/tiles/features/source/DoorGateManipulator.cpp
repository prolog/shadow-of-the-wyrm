#include "DoorGateManipulator.hpp"
#include "Door.hpp"
#include "DoorBreakageCalculator.hpp"
#include "RNG.hpp"

using namespace std;

DoorGateManipulator::DoorGateManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void DoorGateManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  if (creature && current_map)
  {
    DoorPtr door = dynamic_pointer_cast<Door>(feature);

    if (door != nullptr)
    {
      // Is the creature's strength enough to potentially break the door?
      DoorBreakageCalculator dbc;
      int break_chance = dbc.calculate_pct_chance_breakage(creature, door);

      if (break_chance > 0)
      {
        if (RNG::percent_chance(break_chance))
        {
          // ...
        }
        else
        {
          // Add a message that the door buckled but didn't break.
        }
      }
      else
      {
        // If there was no chance at all of breaking the door, add a message to
        // that effect.
      }
    }
  }
}

bool DoorGateManipulator::handle(TilePtr tile, CreaturePtr creature)
{
  bool result = false;

  shared_ptr<Door> door = dynamic_pointer_cast<Door>(feature);

  if (door != nullptr)
  {
    LockPtr lock = door->get_lock();
    EntranceState& entrance_state = door->get_state_ref();
    EntranceStateType state = entrance_state.get_state();

    switch (state)
    {
        // If the door is smashed, nothing can be done.
      case EntranceStateType::ENTRANCE_TYPE_DESTROYED:
        break;

      case EntranceStateType::ENTRANCE_TYPE_OPEN:
        result = door->close();
        break;

      case EntranceStateType::ENTRANCE_TYPE_CLOSED:
        // If the door is closed and locked, try to unlock it.
        // If the door is closed and unlocked, open it.
      default:
        result = door->open();
        break;
    }
  }

  return result;
}