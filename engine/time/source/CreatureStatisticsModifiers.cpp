#include "CreatureStatisticsModifiers.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"

using namespace std;

void CreatureStatisticsModifiers::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    map<double, vector<StatisticsModifier>>& creature_modifiers = creature->get_statistics_modifiers_ref();

    for (auto& m_it = creature_modifiers.begin(); m_it != creature_modifiers.end(); )
    {
      Game& game = Game::instance();

      double modifier_expiry = m_it->first;
      double current_seconds = GameUtils::get_seconds(game);

      if (modifier_expiry <= current_seconds)
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

