#include "WorldWeatherUpdater.hpp"
#include "CoordUtils.hpp"
#include "Game.hpp"
#include "RNG.hpp"

using namespace std;

const int WorldWeatherUpdater::WEATHER_UPDATE_HOURS = 6;
const int WorldWeatherUpdater::WEATHER_UPDATE_RADIUS = 6;

bool WorldWeatherUpdater::should_update_weather(const int cur_hour) const
{
  return ((cur_hour % WEATHER_UPDATE_HOURS) == 0);;
}

void WorldWeatherUpdater::update_world_map_weather(WorldPtr world)
{
  if (world != nullptr)
  {
    Game& game = Game::instance();
    MapPtr world_map = world->get_world(game.get_map_registry_ref());

    if (world_map != nullptr)
    {
      TilesContainer tiles = world_map->get_tiles();

      // Update the weather for the tiles around the player.
      Coordinate player_coord = world_map->get_location(CreatureID::CREATURE_ID_PLAYER);
      vector<Coordinate> weather_update_coords = CoordUtils::get_adjacent_map_coordinates(world_map->size(), player_coord.first, player_coord.second, WEATHER_UPDATE_RADIUS);

      for (auto& weather_coord : weather_update_coords)
      {
        TilePtr tile = world_map->at(weather_coord);

        if (tile != nullptr)
        {
          Weather weather = tile->get_weather();
          weather = update_weather_data(weather);
          tile->set_weather(weather);
        }
      }
    }
  }
}

// JCD FIXME turn this into a calculator once this gets more complex.
Weather WorldWeatherUpdater::update_weather_data(const Weather& weather)
{
  Weather w = weather;

  int wind_speed = weather.get_wind_speed();
  int amount = RNG::range(0, 20);
  bool increase = RNG::percent_chance(50);
  if (increase == false)
  {
    amount = amount * -1;
  }

  int new_amount = wind_speed + amount;
  new_amount = std::max(new_amount, 0);
  new_amount = std::min(new_amount, 100);

  return w;
}

