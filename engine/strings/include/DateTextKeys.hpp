#pragma once
#include <string>
#include "CalendarTypes.hpp"
#include "Date.hpp"

class DateTextKeys
{
  public:
    static std::string get_date_time_message(const Date& date, const std::string& season_sid, const PhaseOfMoonType pom);
    static std::string get_time(const Date& date);
    static std::string get_phase_of_moon_sid(const PhaseOfMoonType pom);
    
  protected:
    static const std::string DATE_TIME_MESSAGE;
    static const std::string PHASE_OF_MOON_NEW;
    static const std::string PHASE_OF_MOON_WAXING;
    static const std::string PHASE_OF_MOON_FULL;
    static const std::string PHASE_OF_MOON_WANING;
        
    DateTextKeys();
    ~DateTextKeys();
};
