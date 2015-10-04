#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "DoorGateManipulator.hpp"
#include "Door.hpp"
#include "DoorBreakageCalculator.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

const int DoorGateManipulator::PCT_CHANCE_SPRAIN_LEG_BUCKLE = 4;
const int DoorGateManipulator::PCT_CHANCE_SPRAIN_LEG_UNMOVED = 15;
const int DoorGateManipulator::SPRAIN_DAMAGE_MIN = 2;
const int DoorGateManipulator::SPRAIN_DAMAGE_MAX = 10;

DoorGateManipulator::DoorGateManipulator(FeaturePtr feature)
: IFeatureManipulator(feature)
{
}

void DoorGateManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, FeaturePtr feature)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

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
          break_down_door(creature, feature_tile);
        }
        else
        {
          // Add a message that the door buckled but didn't break.
          manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_DOOR_BUCKLED));
          handle_sprain_if_necessary(creature, PCT_CHANCE_SPRAIN_LEG_BUCKLE);
        }
      }
      else
      {
        // If there was no chance at all of breaking the door, add a message to
        // that effect.
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_DOOR_UNMOVED));
        handle_sprain_if_necessary(creature, PCT_CHANCE_SPRAIN_LEG_UNMOVED);
      }
    }
  }

  manager.send();
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

// Break down the door by removing the door from the tile.
void DoorGateManipulator::break_down_door(CreaturePtr creature, TilePtr tile)
{
  if (creature && tile)
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_DOOR_DESTROYED));

    tile->remove_feature();
  }
}

// When unsuccessfully trying to break down a door, the creature may spain its
// leg.  This deals damage, and has a chance to apply slowness, as well.
void DoorGateManipulator::handle_sprain_if_necessary(CreaturePtr creature, const int pct_chance)
{
  if (creature != nullptr)
  {
    if (RNG::percent_chance(pct_chance))
    {
      IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_SPRAIN_LEG));
      manager.send();

      // Deal damage.
      CreaturePtr no_attacker;
      CombatManager cm;
      cm.deal_damage(no_attacker, creature, RNG::range(SPRAIN_DAMAGE_MIN, SPRAIN_DAMAGE_MAX));

      // Potentially add slow status, due to the gimpy leg.
      StatusEffectPtr status_effect = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_SLOWNESS);

      if (status_effect && status_effect->should_apply_change(creature))
      {
        status_effect->apply_change(creature);
      }
    }
  }
}
