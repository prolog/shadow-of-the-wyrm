#include "CreatureStatisticsModifiers.hpp"

using namespace std;

void CreatureStatisticsModifiers::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    map<ulonglong, vector<StatisticsModifier>>& creature_modifiers = creature->get_statistics_modifiers_ref();

    for (auto& m_it = creature_modifiers.begin(); m_it != creature_modifiers.end(); )
    {
      ulonglong modifier_expiry = m_it->first;

      if (modifier_expiry <= total_minutes_elapsed)
      {
        creature_modifiers.erase(m_it++);
      }
      else
      {
        // Since std::map is ordered by key, once we've hit modifiers that
        // are past the present moment in time, we can stop iterating.
        break;
      }
    }
  }
}

