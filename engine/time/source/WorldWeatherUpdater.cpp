#include "WorldWeatherUpdater.hpp"
#include "CoordUtils.hpp"
#include "Game.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "WeatherCalculator.hpp"

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

// Update the world map weather on to the new map, but only if the new map
// is an overworld map - don't set it for cosmos, underwater, and so on.
void WorldWeatherUpdater::update_weather_for_map(MapPtr old_map, TilePtr old_tile, MapPtr new_map)
{
  if (old_map != nullptr && old_tile != nullptr && new_map != nullptr)
  {
    if (old_map->get_map_type() == MapType::MAP_TYPE_WORLD && new_map->get_map_type() == MapType::MAP_TYPE_OVERWORLD)
    {
      WeatherPtr weather = MapUtils::get_weather(old_map, old_tile);

      if (weather != nullptr)
      {
        new_map->set_weather(*weather);
      }
    }
  }
}

void WorldWeatherUpdater::set_weather(MapPtr map, TilePtr tile, const Weather& w)
{
  if (map != nullptr && tile != nullptr)
  {
    MapType mt = map->get_map_type();

    if (mt == MapType::MAP_TYPE_WORLD)
    {
      tile->set_weather(w);
    }
    else if (mt == MapType::MAP_TYPE_OVERWORLD)
    {
      map->set_weather(w);
    }
  }
}

// JCD FIXME turn this into a calculator once this gets more complex.
Weather WorldWeatherUpdater::update_weather_data(const Weather& weather)
{
  Weather w = weather;
  WeatherCalculator wc;

  w.set_wind_speed(wc.calculate_new_wind_speed(w.get_wind_speed()));

  return w;
}

