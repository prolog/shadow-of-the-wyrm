#pragma once
#include <map>
#include "common.hpp"
#include "CalendarDay.hpp"
#include "CalendarTypes.hpp"
#include "ISeason.hpp"
#include "ISerializable.hpp"

class Date;

class Calendar : public ISerializable
{
  public:
    Calendar();
    bool operator==(const Calendar& c) const;
    
    void set_date(const uint days_elapsed);
    void add_days(const uint days);
    void add_seconds(const double seconds);
    double get_seconds() const;
    double get_seconds_from_date(const Date& date) const;
    Date get_date() const;
    ISeasonPtr get_season() const;
    uint get_starting_year() const;
    
    bool update_season_if_necessary();

    void set_calendar_days(const std::map<int, CalendarDay>& new_calendar_days);
    std::map<int, CalendarDay>& get_calendar_days_ref();

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
    
  protected:
    // Number of seconds since day 1 of month 1 of year 832.
    // This actually needs to be floating point to account for edge cases where
    // creatures have very low speeds (e.g., 1).
    double seconds;
    uint STARTING_YEAR;
    ISeasonPtr season;
    std::map<int, CalendarDay> calendar_days;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
