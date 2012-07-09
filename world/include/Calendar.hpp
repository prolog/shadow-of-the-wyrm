#pragma once
#include <map>
#include "common.hpp"
#include "CalendarTypes.hpp"
#include "ISeason.hpp"

class Date;

class Calendar
{
  public:
    Calendar();
    
    void add_days(const uint days);
    void add_seconds(const double seconds);

    Date get_date() const;
    ISeasonPtr get_season() const;
    
  protected:
    void update_season_if_necessary(const double seconds, const double additional_seconds);
    
    // Number of seconds since day 1 of month 1 of year 832.
    // This actually needs to be floating point to account for edge cases where
    // creatures have very low speeds (e.g., 1).
    double seconds;
    const uint STARTING_YEAR;
    ISeasonPtr season;
};
