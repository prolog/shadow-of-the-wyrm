#include <boost/foreach.hpp>
#include "Commands.hpp"
#include "FeatureAction.hpp"
#include "Game.hpp"
#include "KeyManager.hpp"
#include "MapUtils.hpp"
#include "MessageManager.hpp"
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
  ActionCostValue apply_cost = 0;
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
    }
    else if (num_features == 1)
    {
      TilePtr tile = features.begin()->second;
      FeaturePtr feature = tile->get_feature();
      handled = handle(feature, creature, tile->get_creature());
    }
    else
    {
      handled = apply_multiple_options(creature, features);
    }

    if (handled)
    {
      apply_cost = get_action_cost_value();
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

  MessageManager& manager = MessageManager::instance();
  manager.add_new_message(StringTable::get(lock_message_sid));

  return lock_handled;
}

void FeatureAction::send_application_messages()
{
  MessageManager& manager = MessageManager::instance();  
  manager.send();
}

// Handle a particular terrain feature
bool FeatureAction::handle(FeaturePtr feature, CreaturePtr creature, const bool tile_has_creature)
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
      result = feature->handle();

      if (result)
      {
        string handle_message_sid = feature->get_handle_message_sid();

        if (!handle_message_sid.empty())
        {
          add_application_message(handle_message_sid);
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

  send_application_messages();

  return result;
}

void FeatureAction::add_application_message(const string& app_msg_sid)
{
  MessageManager& manager = MessageManager::instance();

  manager.add_new_message(StringTable::get(app_msg_sid));
}

// When there are features present in multiple directions, force the creature
// to choose one.
bool FeatureAction::apply_multiple_options(CreaturePtr creature, const TileDirectionMap& tile_map) 
{
  bool applied = false;

  // Make the creature select a direction.
  CommandFactoryPtr command_factory    = boost::make_shared<CommandFactory>();
  KeyboardCommandMapPtr kb_command_map = boost::make_shared<KeyboardCommandMap>();

  // If the creature is the player, inform the player that a direction is needed.
  if (creature->get_is_player())
  {
    add_application_message(ActionTextKeys::ACTION_GET_DIRECTION);
  }

  // Try to get a direction.  This might fail.
  CommandPtr base_command = creature->get_decision_strategy()->get_decision(creature->get_id(), command_factory, kb_command_map);

  if (base_command)
  {
    // Check to see if it's an actual directional command
    boost::shared_ptr<DirectionalCommand> dcommand;
    dcommand = boost::dynamic_pointer_cast<DirectionalCommand>(base_command);

    if (dcommand)
    {
      // It was an actual directional command.  Check to see if there's
      // a terrain feature in that direction.
      Direction requested_direction = dcommand->get_direction();

      TileDirectionMap::const_iterator t_it = tile_map.find(requested_direction);

      if (t_it != tile_map.end())
      {
        TilePtr tile = t_it->second;
        FeaturePtr feature = tile->get_feature();
        applied = handle(feature, creature, tile->get_creature());
      }
    }
  }

  return applied;
}

// Inform the creature that there are no features that can be applied.
void FeatureAction::inform_no_features(CreaturePtr creature)
{
  string no_features = ActionTextKeys::ACTION_APPLY_NO_FEATURES_PRESENT;
  add_application_message(no_features);
}

// Default cost of applying/handling a terrain feature.
ActionCostValue FeatureAction::get_action_cost_value() const
{
  return 1;
}