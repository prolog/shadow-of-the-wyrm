#pragma once
#include "Map.hpp"
#include "Weather.hpp"
#include "World.hpp"

class WorldWeatherUpdater
{
  public:
    bool should_update_weather(const int cur_hour) const;
    void update_world_map_weather(WorldPtr world);
    void update_weather_for_map(MapPtr old_map, TilePtr old_tile, MapPtr new_map);
    Weather update_weather_data(const Weather& w);

  protected:
    static const int WEATHER_UPDATE_HOURS;
    static const int WEATHER_UPDATE_RADIUS;
};