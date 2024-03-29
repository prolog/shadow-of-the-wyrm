#pragma once
#include <map>
#include <string>
#include "common.hpp"
#include "Colours.hpp"
#include "ISerializable.hpp"

namespace DateValues
{
  static const int NUMBER_OF_MONTHS = 12;
  static const int NUMBER_OF_DAYS = 7;
  static const int NUMBER_OF_DAYS_PER_MONTH = 30;
  static const int NUMBER_OF_DAYS_PER_YEAR = 360;
};

enum struct TimeOfDayType
{
  TIME_OF_DAY_UNDEFINED = -1,
  TIME_OF_DAY_DAWN = 0,
  TIME_OF_DAY_DAY = 1,
  TIME_OF_DAY_DUSK = 2,
  TIME_OF_DAY_NIGHT = 3
};

constexpr auto CTIME_OF_DAY_UNDEFINED = -1;
constexpr auto CTIME_OF_DAY_DAWN = 0;
constexpr auto CTIME_OF_DAY_DAY = 1;
constexpr auto CTIME_OF_DAY_DUSK = 2;
constexpr auto CTIME_OF_DAY_NIGHT = 3;

class TimeOfDay
{
  public:
    static std::pair<Colour, Colour> get_time_of_day_colours(const TimeOfDayType tod, const bool on_overworld_map, const bool shade_terrain, const bool shade_creatures_items);
    static std::pair<bool, TimeOfDayType> get_is_transition_hour(const uint current_hour);

    static const uint TIME_OF_DAY_DAWN;
    static const uint TIME_OF_DAY_DAY;
    static const uint TIME_OF_DAY_DUSK;
    static const uint TIME_OF_DAY_NIGHT;

  protected:
    static void initialize_colour_overrides();

    // First colour is tile colour, if nothing there.
    // Second colour is if anything (creature, item, feature) is on tile.
    static std::map<TimeOfDayType, std::pair<Colour, Colour>> time_of_day_colour_overrides;
};

class Date : public ISerializable
{
  public:
    Date(const uint sec, const uint min, const uint hrs, const uint day_week, const uint day_month, const uint day_year, const uint month, const uint year);
    Date(const std::string& serialized_date_str);
    static Date null();
    bool operator==(const Date& d) const;

    bool get_days_equal(const Date& d) const;

    uint get_seconds() const;
    uint get_minutes() const;
    uint get_hours() const;
    TimeOfDayType get_time_of_day() const;
    uint get_day_of_week() const;
    std::string get_day_of_week_sid() const;
    uint get_day_of_month() const;
    uint get_day_of_year() const;
    uint get_month() const;
    std::string get_month_sid() const;
    uint get_year() const;

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    uint seconds;
    uint minutes;
    uint hours;
    uint day_of_week;
    uint day_of_month;
    uint day_of_year;
    uint month;
    uint year;
    
    static std::string month_sids[DateValues::NUMBER_OF_MONTHS];
    static std::string day_of_week_sids[DateValues::NUMBER_OF_DAYS];

    ClassIdentifier internal_class_identifier() const override;
};
