#pragma once

class Weather
{
  public:
    Weather(const std::string& wind_speed);

    int get_wind_speed() const;

  protected:
    int wind_speed;
};


