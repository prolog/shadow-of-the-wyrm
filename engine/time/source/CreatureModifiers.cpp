#include "CreatureCalculator.hpp"
#include "CreatureModifiers.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

void CreatureModifiers::tick(CreaturePtr creature, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  bool removed = false;

  if (creature)
  {
    map<double, vector<pair<string, Modifier>>>& creature_modifiers = creature->get_modifiers_ref();

    for (auto& m_it = creature_modifiers.begin(); m_it != creature_modifiers.end(); )
    {
      Game& game = Game::instance();

      double modifier_expiry = m_it->first;
      double current_seconds = GameUtils::get_seconds(game);

      vector<pair<string, Modifier>> modifiers = m_it->second;

      if ((modifier_expiry > 0) && (modifier_expiry <= current_seconds))
      {
        process_current_modifiers(creature, modifiers);

        add_removal_message(creature);
        creature_modifiers.erase(m_it++);

        // Removed at least one entry - we need to update the creature's
        // calculated values.
        removed = true;
      }
      else
      {
        // Since std::map is ordered by key, once we've hit modifiers that
        // are past the present moment in time, we can stop iterating.
        break;
      }
    }

    if (removed)
    {
      CreatureCalculator::update_calculated_values(creature);
    }
  }
}

// Process the current set of modifiers for the given second.
// Basically, if there are any status
void CreatureModifiers::process_current_modifiers(CreaturePtr creature, const vector<pair<string, Modifier>>& modifiers)
{
  for (const auto& mod_pair : modifiers)
  {
    Modifier m = mod_pair.second;
    vector<string> statuses = m.get_affected_status_keys();

    for (const auto& status : statuses)
    {
      StatusEffectPtr status_p = StatusEffectFactory::create_status_effect(status);

      if (status_p && creature->has_status(status))
      {
        status_p->finalize_change(creature);
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