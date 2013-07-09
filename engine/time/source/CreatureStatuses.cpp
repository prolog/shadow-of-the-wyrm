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
      StatusEffectPtr status_change = StatusEffectFactory::create_status_change(status_id);
      StatusDuration cur_duration = durations[status_id];
      double end = cur_duration.get_end();

      if (current_seconds > end)
      {
        status_change->finalize_change(creature);
      }
      else
      {
        status_change->tick(creature);
      }
    }
  }
}

