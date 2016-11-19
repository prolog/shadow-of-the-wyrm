#include "WorldTimeObserver.hpp"
#include "DateTextKeys.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "Serialize.hpp"

using namespace std;

WorldTimeObserver::WorldTimeObserver()
: ITimeObserver(), tod_transition_sids({{TimeOfDayType::TIME_OF_DAY_DAWN, DateTextKeys::TIME_TRANSITION_DAWN},
                                        {TimeOfDayType::TIME_OF_DAY_DAY, DateTextKeys::TIME_TRANSITION_DAY}, 
                                        {TimeOfDayType::TIME_OF_DAY_DUSK, DateTextKeys::TIME_TRANSITION_DUSK},
                                        {TimeOfDayType::TIME_OF_DAY_NIGHT, DateTextKeys::TIME_TRANSITION_NIGHT}})
{
}

void WorldTimeObserver::notify(const ulonglong minutes_this_tick)
{
  Game& game = Game::instance();

  WorldPtr world = game.get_current_world();

  if (world)
  {
    Calendar& calendar = world->get_calendar();
    Date date = calendar.get_date();

    uint cur_hour = date.get_hours();
    auto tod_details = TimeOfDay::get_is_transition_hour(cur_hour);
    bool update_time_of_day = tod_details.first;

    if (update_time_of_day)
    {
      redraw_and_update_time_of_day(tod_details.second);
    }
  }
}

void WorldTimeObserver::redraw_and_update_time_of_day(const TimeOfDayType tod)
{
  Game& game = Game::instance();
  MapPtr map = game.get_current_map();

  // We only care about map transitions on the overworld.
  // On the world map, it would occur too frequently when moving around.
  // Underground, it's always semi-night.
  if (map != nullptr && map->get_map_type() == MapType::MAP_TYPE_OVERWORLD)
  {
    auto t_it = tod_transition_sids.find(tod);

    if (t_it != tod_transition_sids.end())
    {
      // Force a display update.
      CreaturePtr player = game.get_current_player();
      game.update_display(player, game.get_current_map(), player->get_decision_strategy()->get_fov_map(), true);

      // Show a message about the time change.
      string time_sid = t_it->second;

      if (!time_sid.empty())
      {
        IMessageManager& manager = MM::instance();
        manager.add_new_message(StringTable::get(time_sid));
        manager.send();
      }
    }
  }
}

ITimeObserver* WorldTimeObserver::clone()
{
  return new WorldTimeObserver(*this);
}

ClassIdentifier WorldTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WORLD_TIME_OBSERVER;
}

