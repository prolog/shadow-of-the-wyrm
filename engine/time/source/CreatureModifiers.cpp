#include "CreatureModifiers.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"

using namespace std;

void CreatureModifiers::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    map<double, vector<pair<string, Modifier>>>& creature_modifiers = creature->get_modifiers_ref();

    for (auto& m_it = creature_modifiers.begin(); m_it != creature_modifiers.end(); )
    {
      Game& game = Game::instance();

      double modifier_expiry = m_it->first;
      double current_seconds = GameUtils::get_seconds(game);

      if (modifier_expiry <= current_seconds)
      {
        add_removal_message(creature);
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

void CreatureModifiers::add_removal_message(CreaturePtr creature)
{
  if (creature)
  {
    string creature_id = creature->get_id();

    // Check to see if the creature is the player, or in view of the player.

    // Add the appropriate message.
  }
}