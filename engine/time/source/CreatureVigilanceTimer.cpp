#include "CreatureVigilanceTimer.hpp"
#include "CreatureProperties.hpp"

CreatureVigilanceTimer::CreatureVigilanceTimer()
: interval(0)
{
}

CreatureVigilanceTimer::CreatureVigilanceTimer(const uint new_interval)
: interval(new_interval)
{
}

// When this timer is called, the creature becomes less vigilant, and can be
// backstabbed again.
void CreatureVigilanceTimer::tick(CreaturePtr creature, TilePtr /*tile*/, const ulonglong /*minutes_this_tick*/, const ulonglong total_minutes_elapsed)
{
  if (total_minutes_elapsed % interval == 0)
  {
    if (creature != nullptr)
    {
      creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_BACKSTABBED);
    }
  }
}
