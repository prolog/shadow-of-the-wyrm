#include <boost/foreach.hpp>
#include "CreatureStatuses.hpp"
#include "Game.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

void CreatureStatuses::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    Game& game = Game::instance();
    double current_seconds = game.get_current_world()->get_calendar().get_seconds();

    CreatureStatusMap statuses = creature->get_statuses();
    StatusDurationMap durations = creature->get_status_durations();

    BOOST_FOREACH(CreatureStatusMap::value_type& status, statuses)
    {
      string status_id = status.first;
      StatusEffectPtr status_effect = StatusEffectFactory::create_status_effect(status_id);
      StatusDuration cur_duration = durations[status_id];
      double end = cur_duration.get_end();

      // A value of -1 indicates permanence.
      if ((current_seconds > end) && (end >= 0))
      {
        status_effect->finalize_change(creature);
      }
      else
      {
        status_effect->tick(creature);
      }
    }
  }
}

