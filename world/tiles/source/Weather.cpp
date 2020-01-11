#include "Weather.hpp"
#include "Conversion.hpp"
#include "Serialize.hpp"

using namespace std;

bool Weather::operator==(const Weather& w) const
{
  bool result = true;

  result = result && (wind_speed == w.wind_speed);

  return result;
}

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

bool Weather::serialize(ostream& stream) const
{
  Serialize::write_int(stream, wind_speed);
  return true;
}

bool Weather::deserialize(istream& stream)
{
  Serialize::read_int(stream, wind_speed);
  return true;
}

ClassIdentifier Weather::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_WEATHER;
}

#ifdef UNIT_TESTS
#include "unit_tests/Weather_test.cpp"
#endif

