#include "Weather.hpp"
#include "Conversion.hpp"

using namespace std;

Weather::Weather(const string& new_wind_speed)
: wind_speed(0)
{
  if (!new_wind_speed.empty())
  {
    wind_speed = String::to_int(new_wind_speed);
  }
}

void Weather::set_wind_speed(const int new_wind_speed)
{
  wind_speed = new_wind_speed;
}

int Weather::get_wind_speed() const
{
  return wind_speed;
}

#ifdef UNIT_TESTS
#include "unit_tests/Weather_test.cpp"
#endif

