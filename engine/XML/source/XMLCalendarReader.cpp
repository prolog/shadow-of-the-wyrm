#include "XMLCalendarReader.hpp"

using namespace std;

map<int, CalendarDay> XMLCalendarReader::get_calendar_days(const XMLNode& calendar_node)
{
  map<int, CalendarDay> cal_days;

  if (!calendar_node.is_null())
  {
    vector<XMLNode> calendar_day_nodes = XMLUtils::get_elements_by_local_name(calendar_node, "Day");

    for (const XMLNode& day_node : calendar_day_nodes)
    {
      CalendarDay cd;
      parse_calendar_day(cd, day_node);

      cal_days[cd.get_calendar_day()] = cd;
    }
  }

  return cal_days;
}

void XMLCalendarReader::parse_calendar_day(CalendarDay& cd, const XMLNode& calendar_day_node)
{
  if (!calendar_day_node.is_null())
  {
    string name_sid = XMLUtils::get_child_node_value(calendar_day_node, "NameSID");
    string desc_sid = XMLUtils::get_child_node_value(calendar_day_node, "DescriptionSID");
    int day = XMLUtils::get_child_node_int_value(calendar_day_node, "CalendarDay", cd.get_calendar_day());

    cd.set_name_sid(name_sid);
    cd.set_description_sid(desc_sid);
    cd.set_calendar_day(day);
  }
}
