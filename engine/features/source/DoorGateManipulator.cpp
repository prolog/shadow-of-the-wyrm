#include "DoorGateManipulator.hpp"
#include "Door.hpp"

using namespace std;

DoorGateManipulator::DoorGateManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void DoorGateManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
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