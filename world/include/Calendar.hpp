#pragma once
#include <map>
#include "common.hpp"
#include "CalendarDay.hpp"
#include "CalendarTypes.hpp"
#include "Date.hpp"
#include "ISeason.hpp"
#include "ISerializable.hpp"

class Calendar : public ISerializable
{
  public:
    Calendar();
    bool operator==(const Calendar& c) const;
    Calendar(const Calendar& c) = delete;
    bool operator=(const Calendar& c) = delete;
    
    void set_date(const uint days_elapsed, const uint hours_elapsed);
    void add_days(const uint days);
    void add_seconds(const double seconds);
    double get_seconds() const;
    double get_seconds_from_date(const Date& date) const;
    Date get_date() const;
    Date get_date(const double sec_since_start) const;

    ISeason* get_season() const;
    uint get_starting_year() const;
    
    bool update_season_if_necessary();

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
    
  protected:
    // Number of seconds since day 1 of month 1 of year 832.
    // This actually needs to be floating point to account for edge cases where
    // creatures have very low speeds (e.g., 1).
    double seconds;
    uint STARTING_YEAR;
    ISeasonPtr season;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
