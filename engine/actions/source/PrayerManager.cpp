#include "PrayerManager.hpp"

PrayerManager::PrayerManager()
{
}

// Create the decision strategies surrounding prayer, based on the
// creature's chosen deity.
ActionCostValue PrayerManager::pray(CreaturePtr creature)
{
  if (creature)
  {
    // JCD FIXME
  }

  return get_action_cost_value();
}

ActionCostValue PrayerManager::get_action_cost_value() const
{
  return 1;
}
