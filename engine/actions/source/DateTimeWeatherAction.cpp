#include "Date.hpp"
#include "DateTextKeys.hpp"
#include "DateTimeWeatherAction.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "PhaseOfMoonCalculator.hpp"

using std::string;

DateTimeWeatherAction::DateTimeWeatherAction()
{
}

ActionCostValue DateTimeWeatherAction::date_and_time_and_weather()
{
  Game& game = Game::instance();
  IMessageManager& manager = MM::instance();
  
  // Get the date from the game's current world's calendar
  World* world = game.get_current_world();
    
  if (world)
  {
    Calendar& calendar = world->get_calendar();
    Date date = calendar.get_date();
    ISeason* season = calendar.get_season();
    PhaseOfMoonCalculator pomc;
    MapPtr map = game.get_current_map();
    CreaturePtr player = game.get_current_player();

    WeatherPtr weather = MapUtils::get_weather(map, MapUtils::get_tile_for_creature(map, player));
    int wind_speed = 0;

    if (weather != nullptr)
    {
      wind_speed = weather->get_wind_speed();
    }

    string date_time_weather_message = DateTextKeys::get_date_time_weather_message(date, season->get_description_sid(), pomc.calculate_phase_of_moon(calendar.get_seconds()), DateTextKeys::get_wind_sid(wind_speed));
      
    manager.add_new_message(date_time_weather_message);
    manager.send();
  }

  CreaturePtr nullc;
  return get_action_cost_value(nullc);
}

// Displaying the date/time/weather is a non-advancing action.
ActionCostValue DateTimeWeatherAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 0;
}
