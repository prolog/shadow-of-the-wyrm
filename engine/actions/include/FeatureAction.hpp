#pragma once
#include "Feature.hpp"
#include "IActionManager.hpp"

// A class to encapsulate handling blocking terrain features 
// (opening doors, pulling levers, etc) that have generic handling
// capabilities.
class FeatureAction : public IActionManager
{
  public:
    FeatureAction();
    ~FeatureAction();
    
    // Apply a terrain feature for a particular creature, by handling it.  This
    // allows creatures to do things like open doors, pull levers, etc.
    ActionCostValue apply(CreaturePtr creature);

    // Handle a given lock.
    bool handle_lock(LockPtr lock, CreaturePtr creature);

    // Handle a given terrain feature.  This method can be called by other managers that
    // need handling functionality, but shouldn't be called directly to "handle something
    // for a particular creature" - that functionality is encapsulated by handle(CreaturePtr).
    bool handle(FeaturePtr feature, CreaturePtr creature, const bool feature_tile_has_creature);

  protected:
    // If the creature is the player, inform them that there are no features
    // to be applied.
    void inform_no_features(CreaturePtr creature);
    void add_application_message(const std::string& app_message_sid);
    void send_application_messages();

    // Try to apply a terrain feature in a certain direction, when multiple
    // options are available.
    bool apply_multiple_options(CreaturePtr creature, const std::map<Direction, TilePtr>& direction_map);

    ActionCostValue get_action_cost_value() const;
};

