#pragma once
#include <utility>
#include "Calendar.hpp"
#include "XMLDataStructures.hpp"
#include "XMLReader.hpp"

class XMLCalendarReader : public XMLReader
{
  public:
    std::map<int, CalendarDay> get_calendar_days(const XMLNode& calendar_node);

  protected:
    void parse_calendar_day(CalendarDay& cd, const XMLNode& calendar_day_node);
};
