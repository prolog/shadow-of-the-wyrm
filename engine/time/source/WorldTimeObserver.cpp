#include "WorldTimeObserver.hpp"
#include "DateTextKeys.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "Serialize.hpp"
#include "WorldWeatherUpdater.hpp"

using namespace std;

WorldTimeObserver::WorldTimeObserver()
: ITimeObserver(), tod_transition_sids({{TimeOfDayType::TIME_OF_DAY_DAWN, DateTextKeys::TIME_TRANSITION_DAWN},
                                        {TimeOfDayType::TIME_OF_DAY_DAY, DateTextKeys::TIME_TRANSITION_DAY}, 
                                        {TimeOfDayType::TIME_OF_DAY_DUSK, DateTextKeys::TIME_TRANSITION_DUSK},
                                        {TimeOfDayType::TIME_OF_DAY_NIGHT, DateTextKeys::TIME_TRANSITION_NIGHT}})
{
}

void WorldTimeObserver::notify(const ulonglong /*minutes_this_tick*/)
{
  Game& game = Game::instance();

  World* world = game.get_current_world();

  if (world)
  {
    Calendar& calendar = world->get_calendar();
    Date date = calendar.get_date();

    uint cur_hour = date.get_hours();
    auto tod_details = TimeOfDay::get_is_transition_hour(cur_hour);
    bool update_time_of_day = tod_details.first;

    WorldWeatherUpdater wwu;
    bool update_weather = wwu.should_update_weather(cur_hour);

    if (update_time_of_day)
    {
      redraw_and_update_time_of_day(tod_details.second);
    }

    if (update_weather)
    {
      wwu.update_world_map_weather(world);
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
  if (map != nullptr && MapUtils::get_supports_time_of_day(map->get_map_type()))
  {
    auto t_it = tod_transition_sids.find(tod);

    if (t_it != tod_transition_sids.end())
    {
      // Force a display update.
      CreaturePtr player = game.get_current_player();

      if (player != nullptr)
      {
        game.update_display(player, game.get_current_map(), player->get_decision_strategy()->get_fov_map(), true);
      }

      // Show a message about the time change.
      string time_sid = t_it->second;

      if (!time_sid.empty())
      {
        IMessageManager& manager = MMF::instance();
        manager.add_new_message(StringTable::get(time_sid));
        manager.send();
      }
    }
  }
}

std::unique_ptr<ITimeObserver> WorldTimeObserver::clone()
{
  std::unique_ptr<ITimeObserver> wto = std::make_unique<WorldTimeObserver>(*this);
  return wto;
}

ClassIdentifier WorldTimeObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WORLD_TIME_OBSERVER;
}

