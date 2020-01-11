#pragma once
#include <map>
#include <string>
#include <vector>
#include "Date.hpp"
#include "ICreatureRegeneration.hpp"
#include "ITimeObserver.hpp"
#include "World.hpp"

// The world time observer handles dawn/dusk transitions.
class WorldTimeObserver : public ITimeObserver
{
  public:
    WorldTimeObserver();
    
    void notify(const ulonglong minutes_elapsed) override;
    ITimeObserver* clone();

    // No override for save/load - no new members.

  protected:
    void redraw_and_update_time_of_day(const TimeOfDayType tod);

    std::map<TimeOfDayType, std::string> tod_transition_sids;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
