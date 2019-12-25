#pragma once
#include <string>
#include "CalendarTypes.hpp"
#include "Date.hpp"

class DateTextKeys
{
  public:
    static std::string get_date_time_weather_message(const Date& date, const std::string& season_sid, const PhaseOfMoonType pom);
    static std::string get_time(const Date& date);
    static std::string get_phase_of_moon_sid(const PhaseOfMoonType pom);

    static const std::string TIME_TRANSITION_DAWN;
    static const std::string TIME_TRANSITION_DAY;
    static const std::string TIME_TRANSITION_DUSK;
    static const std::string TIME_TRANSITION_NIGHT;

  protected:
    static const std::string DATE_TIME_WEATHER_MESSAGE;
    static const std::string TIME_OF_DAY_DAY;
    static const std::string TIME_OF_DAY_NIGHT;
    static const std::string TIME_OF_DAY_DAWN;
    static const std::string TIME_OF_DAY_DUSK;
    static const std::string PHASE_OF_MOON_NEW;
    static const std::string PHASE_OF_MOON_WAXING;
    static const std::string PHASE_OF_MOON_FULL;
    static const std::string PHASE_OF_MOON_WANING;
        
    DateTextKeys();
    ~DateTextKeys();
};
