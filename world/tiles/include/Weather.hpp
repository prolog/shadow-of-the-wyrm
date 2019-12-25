#pragma once

class Weather
{
  public:
    Weather(const std::string& wind_speed);

    void set_wind_speed(const int new_wind_speed);

    int get_wind_speed() const;

  protected:
    int wind_speed;
};


