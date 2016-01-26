#pragma once
#include <string>
#include "ISerializable.hpp"

class CalendarDay : public ISerializable
{
  public:
    CalendarDay(const std::string& new_name_sid, const std::string& new_description_sid, const int new_calendar_day);
    CalendarDay();

    bool operator==(const CalendarDay& cd) const;

    void set_name_sid(const std::string& new_name_sid);
    std::string get_name_sid() const;

    void set_description_sid(const std::string& new_description_sid);
    std::string get_description_sid() const;

    void set_calendar_day(const int new_calendar_day);
    int get_calendar_day() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    std::string name_sid;
    std::string description_sid;
    int calendar_day;

  private:
    ClassIdentifier internal_class_identifier() const override;
};

