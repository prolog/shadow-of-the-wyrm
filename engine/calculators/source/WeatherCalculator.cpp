#include "WeatherCalculator.hpp"
#include "RNG.hpp"

const int WeatherCalculator::STORM_WIND_SPEED_THRESHOLD = 75;
const int WeatherCalculator::PCT_CHANCE_STORM_DISSIPATION = 25;
const int WeatherCalculator::MAX_WIND_SPEED = 150;

int WeatherCalculator::calculate_new_wind_speed(const int wind_speed) const
{
  // Storms have a chance of dying down
  if (wind_speed >= STORM_WIND_SPEED_THRESHOLD)
  {
    if (RNG::percent_chance(PCT_CHANCE_STORM_DISSIPATION))
    {
      return 0;
    }
  }

  // If the weather system hasn't played itself out, vary the wind intensity
  // a bit.
  int amount = RNG::range(0, 20);
  bool increase = RNG::percent_chance(50);
  if (increase == false)
  {
    amount = amount * -1;
  }

  int new_ws = wind_speed + amount;
  new_ws = std::max(new_ws, 0);
  new_ws = std::min(new_ws, MAX_WIND_SPEED);

  return new_ws;
}
