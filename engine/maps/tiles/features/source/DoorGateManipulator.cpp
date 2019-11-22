#include "ActionTextKeys.hpp"
#include "CombatManager.hpp"
#include "DoorGateManipulator.hpp"
#include "Door.hpp"
#include "DoorBreakageCalculator.hpp"
#include "Game.hpp"
#include "HostilityManager.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "StatisticsMarker.hpp"
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

void DoorGateManipulator::kick(CreaturePtr creature, MapPtr current_map, TilePtr feature_tile, const Coordinate& feature_coord, FeaturePtr feature)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

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
          MapPtr current_map = Game::instance().get_current_map();

          break_down_door(creature, feature_tile);
          MapUtils::anger_shopkeeper_if_necessary(feature_coord, current_map, creature);

          // Breaking down a shop's door will anger the shopkeeper.

          // Breaking down doors with a solid kick is pretty impressive,
          // and marks Strength.
          StatisticsMarker sm;

          for (int i = 0; i < RNG::range(2, 4); i++)
          {
            sm.mark_strength(creature);
          }
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

  std::shared_ptr<Door> door = dynamic_pointer_cast<Door>(feature);

  if (door != nullptr && tile != nullptr)
  {
    LockPtr lock = door->get_lock();
    EntranceState& entrance_state = door->get_state_ref();
    EntranceStateType state = entrance_state.get_state();

    // Is there something in the way?
    bool items_block_doorway = tile->get_items()->has_items();

    if (items_block_doorway)
    {
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_DOOR_BLOCKED));
      manager.send();
    }
    else
    {
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
  }

  return result;
}

bool DoorGateManipulator::drop(CreaturePtr dropping_creature, TilePtr tile, ItemPtr item)
{
  return false;
}

// Break down the door by removing the door from the tile.
void DoorGateManipulator::break_down_door(CreaturePtr creature, TilePtr tile)
{
  if (creature && tile)
  {
    IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
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
      IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
      manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_KICK_SPRAIN_LEG));
      manager.send();

      // Deal damage.
      CreaturePtr no_attacker;
      CombatManager cm;
      int sprain_damage = RNG::range(SPRAIN_DAMAGE_MIN, SPRAIN_DAMAGE_MAX);
      Damage sprain_default;
      sprain_default.set_modifier(sprain_damage);
      string source_id; // even if the damage kills, don't give exp for it.

      cm.deal_damage(no_attacker, creature, source_id, sprain_damage, sprain_default);

      // Potentially add slow status, due to the gimpy leg.
      StatusEffectPtr status_effect = StatusEffectFactory::create_status_effect(StatusIdentifiers::STATUS_ID_SLOWNESS, creature->get_id());

      if (status_effect && status_effect->should_apply_change(creature))
      {
        status_effect->apply_change(creature, creature->get_level().get_current());
      }
    }
  }
}
