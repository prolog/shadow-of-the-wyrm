#include "ActionTextKeys.hpp"
#include "Commands.hpp"
#include "FeatureAction.hpp"
#include "Game.hpp"
#include "IFeatureManipulatorFactory.hpp"
#include "KeyManager.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "StringTable.hpp"

using namespace std;

FeatureAction::FeatureAction()
{
}

FeatureAction::~FeatureAction()
{
}

// For the given creature, apply a terrain feature.
// - If the creature is the player, and there are no terrain features, display
//   a message.
// - If there is one terrain feature adjacent or on the creature's tile, handle
//   it.
// - If there is more than one terrain feature adjacent or on the creature's tile,
//   prompt.
ActionCostValue FeatureAction::apply(CreaturePtr creature)
{
  ActionCostValue apply_cost = ActionCostConstants::NO_ACTION;
  Game& game = Game::instance();

  if (creature)
  {
    bool handled = false;
    MapPtr map = game.get_current_map();

    TileDirectionMap features = MapUtils::get_tiles_with_features(map, creature);
    uint num_features = features.size();

    if (num_features == 0)
    {
      inform_no_features(creature);
      send_application_messages(creature);
    }
    else if (num_features == 1)
    {
      TilePtr tile = features.begin()->second;
      FeaturePtr feature = tile->get_feature();
      handled = handle(tile, feature, creature, tile->get_creature() != nullptr);
    }
    else
    {
      handled = apply_multiple_options(creature, features);
    }

    if (handled)
    {
      apply_cost = get_action_cost_value(creature);
    }
  }

  return apply_cost;
}

// Handle a particular lock.
bool FeatureAction::handle_lock(LockPtr lock, CreaturePtr creature)
{
  bool lock_handled = false;
  string lock_message_sid = ActionTextKeys::ACTION_HANDLE_LOCK_NO_KEY;

  // Check to see if the creature has the correct key for locking or
  // unlocking this lock.
  KeyManager km;
  if (km.has_key(creature, lock))
  {
    lock->handle();
    lock_handled = true;
    lock_message_sid = ActionTextKeys::ACTION_HANDLE_LOCK;
  }

  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  manager.add_new_message(StringTable::get(lock_message_sid));

  return lock_handled;
}

void FeatureAction::send_application_messages(CreaturePtr creature)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());
  manager.send();
}

// Handle a particular terrain feature
bool FeatureAction::handle(TilePtr tile, FeaturePtr feature, CreaturePtr creature, const bool tile_has_creature)
{
  bool result = false;

  if (feature && feature->can_handle(tile_has_creature))
  {
    // Check to see if the lock prevents the handling.
    LockPtr lock = feature->get_lock();
    bool feature_locked = lock && lock->get_locked();
    bool creature_unlocked_lock = false;

    // Check to see if there is a lock, and it is locked.
    if (lock && lock->get_locked())
    {
      creature_unlocked_lock = handle_lock(lock, creature);
    }

    if (feature_locked == false || creature_unlocked_lock)
    {
      IFeatureManipulatorPtr feature_manipulator = IFeatureManipulatorFactory::create_manipulator(feature);

      if (feature_manipulator)
      {
        int num_uses = feature->get_uses();

        if (num_uses == -1 || num_uses >= 1)
        {
          if (feature_manipulator->handle(tile, creature))
          {
            string handle_message_sid = feature->get_handle_message_sid();

            if (!handle_message_sid.empty())
            {
              add_application_message(creature, handle_message_sid);
            }

            // If there was only one usage of the feature remaining, remove
            // the feature from the tile.
            if (num_uses == 1)
            {
              tile->remove_feature();
            }
            else if (num_uses > 1)
            {
              feature->set_uses(num_uses-1);
            }
            // If num_uses is -1, don't decrement it.

            result = true;
          }
        }
      }

      // Now that the door has been closed, check to see if
      // there is a lock, and if the creature hasn't opened it, yet.
      // This will lock the door when closing it.
      if (lock && !creature_unlocked_lock)
      {
        handle_lock(lock, creature);
      }
    }

    // If there's a lock, and the creature didn't unlock it prior to handling
    // the feature, try to lock the feature.
    if (lock && !lock->get_locked() && creature_unlocked_lock == false)
    {
      handle_lock(lock, creature);
    }
  }

  send_application_messages(creature);

  return result;
}

void FeatureAction::add_application_message(CreaturePtr creature, const string& app_msg_sid)
{
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  manager.add_new_message(StringTable::get(app_msg_sid));
}

// When there are features present in multiple directions, force the creature
// to choose one.
bool FeatureAction::apply_multiple_options(CreaturePtr creature, const TileDirectionMap& tile_map) 
{
  bool applied = false;

  // Make the creature select a direction.
  CommandFactoryPtr command_factory    = std::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = std::make_shared<KeyboardCommandMap>();

  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  // If the creature is the player, inform the player that a direction is needed.
  if (creature->get_is_player())
  {
    add_application_message(creature, ActionTextKeys::ACTION_GET_DIRECTION);
    manager.send();
  }

  // Try to get a direction.  This might fail.
  CommandPtr base_command = creature->get_decision_strategy()->get_decision(true, creature->get_id(), command_factory, kb_command_map);

  if (base_command)
  {
    // Check to see if it's an actual directional command
    std::shared_ptr<DirectionalCommand> dcommand;
    dcommand = std::dynamic_pointer_cast<DirectionalCommand>(base_command);

    if (dcommand)
    {
      manager.clear_if_necessary();

      // It was an actual directional command.  Check to see if there's
      // a terrain feature in that direction.
      Direction requested_direction = dcommand->get_direction();

      TileDirectionMap::const_iterator t_it = tile_map.find(requested_direction);

      if (t_it != tile_map.end())
      {
        TilePtr tile = t_it->second;
        FeaturePtr feature = tile->get_feature();
        applied = handle(tile, feature, creature, tile->get_creature() != nullptr);
      }
    }
  }

  return applied;
}

// Inform the creature that there are no features that can be applied.
void FeatureAction::inform_no_features(CreaturePtr creature)
{
  string no_features = ActionTextKeys::ACTION_APPLY_NO_FEATURES_PRESENT;
  add_application_message(creature, no_features);
}

// Default cost of applying/handling a terrain feature.
ActionCostValue FeatureAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}