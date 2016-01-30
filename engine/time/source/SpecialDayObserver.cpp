#include "SpecialDayObserver.hpp"
#include "Game.hpp"
#include "TextMessages.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

void SpecialDayObserver::notify(const ulonglong minutes_passed)
{
  double cur_seconds = 0;
  Game& game = Game::instance();
  WorldPtr world = game.get_current_world();

  if (world != nullptr)
  {
    const Calendar& calendar = world->get_calendar();
    const map<int, CalendarDay>& calendar_days = game.get_calendar_days_ref();

    check_special_day(calendar_days, calendar);
  }
}

void SpecialDayObserver::check_special_day(const std::map<int, CalendarDay>& calendar_days, const Calendar& calendar)
{
  int day_of_year = static_cast<int>(calendar.get_date().get_day_of_year());

  auto cd_it = calendar_days.find(day_of_year);

  if (cd_it != calendar_days.end())
  {
    CalendarDay cd = cd_it->second;
    string day_message = TextMessages::get_special_day_message(cd.get_name_sid(), cd.get_description_sid());

    IMessageManager& manager = MessageManagerFactory::instance();
    manager.add_new_message(day_message);

    manager.send();
  }
}


ITimeObserver* SpecialDayObserver::clone() 
{
  return new SpecialDayObserver(*this);
}

ClassIdentifier SpecialDayObserver::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SPECIAL_DAY_OBSERVER;
}

#ifdef UNIT_TESTS
#include "unit_tests/SpecialDayObserver_test.cpp"
#endif

