#include "CreatureStatuses.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

void CreatureStatuses::tick(CreaturePtr creature, TilePtr tile, const ulonglong /*minutes_this_tick*/, const ulonglong /*total_minutes_elapsed*/)
{
  if (creature)
  {
    CreatureStatusMap statuses = creature->get_statuses();

    // For each status, apply a "tick" - poisoned creatures take damage, etc.
    // This class is purely responsible for iterating over the statuses and
    // ticking - removal of statuses is handled in CreatureModifiers.
    for (const CreatureStatusMap::value_type& status : statuses)
    {
      string status_id = status.first;
      Status st = status.second;
      bool affected = st.get_value();
      int danger_level = st.get_danger_level();

      if (affected)
      {
        string source_id = st.get_source_id();
        StatusEffectPtr status_effect = StatusEffectFactory::create_status_effect(nullptr, status_id, st.get_source_id());

        status_effect->tick(creature, danger_level);
      }
    }
  }
}

