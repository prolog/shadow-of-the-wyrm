#pragma once
#include "ITimeObserver.hpp"
#include "Map.hpp"
#include "Calendar.hpp"

class SpecialDayObserver : public ITimeObserver
{
  public:
    void notify(const ulonglong minutes_elapsed) override;

    ITimeObserver* clone() override;

  protected:
    void check_special_day(const std::map<int, CalendarDay>& calendar_days, const Calendar& calendar);

  private:
    ClassIdentifier internal_class_identifier() const override;
};

