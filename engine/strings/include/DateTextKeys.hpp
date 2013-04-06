#pragma once
#include <string>
#include "Date.hpp"

class DateTextKeys
{
  public:
    static std::string get_date_time_message(const Date& date, const std::string& season_sid);
    static std::string get_time(const Date& date);
    
  protected:
    static const std::string DATE_TIME_MESSAGE;
    
    DateTextKeys();
    ~DateTextKeys();
};
