#pragma once

class WeatherCalculator
{
  public:
    int calculate_new_wind_speed(const int wind_speed) const;
    int calculate_pct_chance_shimmer(const int wind_speed) const;

  protected:
    static const int STORM_WIND_SPEED_THRESHOLD;
    static const int PCT_CHANCE_STORM_DISSIPATION;
    static const int MAX_WIND_SPEED;
    static const int MIN_WIND_SPEED_FOR_SHIMMER;
};
