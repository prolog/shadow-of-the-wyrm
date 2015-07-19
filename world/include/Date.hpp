#pragma once
#include "common.hpp"
#include <string>

namespace DateValues
{
  static const int NUMBER_OF_MONTHS = 12;
  static const int NUMBER_OF_DAYS = 7;
  static const int NUMBER_OF_DAYS_PER_MONTH = 30;
  static const int NUMBER_OF_DAYS_PER_YEAR = 360;
};

class Date
{
  public:
    Date(const uint sec, const uint min, const uint hrs, const uint day_week, const uint day_month, const uint month, const uint year);

    uint get_seconds() const;
    uint get_minutes() const;
    uint get_hours() const;
    uint get_day_of_week() const;
    std::string get_day_of_week_sid() const;
    uint get_day_of_month() const;
    uint get_month() const;
    std::string get_month_sid() const;
    uint get_year() const;

  protected:
    uint seconds;
    uint minutes;
    uint hours;
    uint day_of_week;
    uint day_of_month;
    uint month;
    uint year;
    
    static std::string month_sids[DateValues::NUMBER_OF_MONTHS];
    static std::string day_of_week_sids[DateValues::NUMBER_OF_DAYS];
};
