#include "CreatureStatsIncrementer.hpp"
#include "MessageManagerFactory.hpp"
#include "StatisticTextKeys.hpp"

using namespace std;

CreatureStatsIncrementer::CreatureStatsIncrementer()
: ICreatureRegeneration(),
minutes_interval(0)
{
}

CreatureStatsIncrementer::CreatureStatsIncrementer(const uint new_minutes_interval)
: ICreatureRegeneration(), 
  minutes_interval(new_minutes_interval)
{
}

void CreatureStatsIncrementer::tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    if (total_minutes_elapsed % minutes_interval == 0)
    {
      // Only display stat increase messages if the creature is the player.
      IMessageManager& manager = MessageManagerFactory::instance(creature, creature->get_is_player());
      vector<pair<Statistic&, string>> stat_and_incr = {{creature->get_strength_ref(), StatisticTextKeys::STATISTIC_GAIN_STRENGTH},
                                                        {creature->get_dexterity_ref(), StatisticTextKeys::STATISTIC_GAIN_DEXTERITY},
                                                        {creature->get_agility_ref(), StatisticTextKeys::STATISTIC_GAIN_AGILITY},
                                                        {creature->get_intelligence_ref(), StatisticTextKeys::STATISTIC_GAIN_INTELLIGENCE},
                                                        {creature->get_willpower_ref(), StatisticTextKeys::STATISTIC_GAIN_WILLPOWER},
                                                        {creature->get_charisma_ref(), StatisticTextKeys::STATISTIC_GAIN_CHARISMA}};

      for (auto& stat_pair : stat_and_incr)
      {
        increment_stat_if_necessary(stat_pair, manager);
      }
    }
  }
}

// Increment the stat as necessary.  Whenever the current number of marks is
// greater than the stat, the stat is incremented.  This can happen multiple
// times.
void CreatureStatsIncrementer::increment_stat_if_necessary(pair<Statistic&, string>& stat_pair, IMessageManager& manager)
{
  Statistic& stat = stat_pair.first;
  Marks& marks = stat.get_marks_ref();
  bool incremented_stat = false;

  int marks_cur = marks.get_value();
  while (marks_cur >= stat.get_base())
  {
    marks_cur -= stat.get_base();

    marks.set_value(marks_cur);
    stat.set_base(stat.get_base() + 1);
    stat.set_current(stat.get_current() + 1);

    incremented_stat = true;
  }

  if (incremented_stat)
  {
    manager.add_new_message(StringTable::get(stat_pair.second));
    manager.send();
  }
}
