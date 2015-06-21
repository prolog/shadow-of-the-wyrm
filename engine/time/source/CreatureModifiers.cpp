#include "ActionTextKeys.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureModifiers.hpp"
#include "CreatureUtils.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SpellAdditionalProperties.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

void CreatureModifiers::tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
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
    string spell_id = mod_pair.first;
    Modifier m = mod_pair.second;
    vector<string> statuses = m.get_affected_status_keys();

    add_removal_message(creature, spell_id);

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

void CreatureModifiers::add_removal_message(CreaturePtr creature, const string& spell_id)
{
  if (!spell_id.empty() && creature != nullptr)
  {
    Game& game = Game::instance();
    string creature_id = creature->get_id();

    const SpellMap& spells = game.get_spells_ref();
    auto spell_it = spells.find(spell_id);

    if (spell_it != spells.end())
    {
      Spell spell = spell_it->second;
      string spell_wear_off_sid = spell.get_property(SpellAdditionalProperties::PROPERTY_STATISTIC_MODIFIER_WEAR_OFF_SID);

      // Check to see if the creature is the player, or in view of the player.
      bool affects_player = CreatureUtils::is_player_or_in_los(creature);

      // Get the appropriate message manager and set the appropriate message.
      // If the creature is the player, use the spell wear off sid.
      // Otherwise, use the generic spell wear off message for creatures.
      IMessageManager& manager = MessageManagerFactory::instance(creature, affects_player);

      if (creature->get_is_player())
      {
        manager.add_new_message(StringTable::get(spell_wear_off_sid));
      }
      else
      {
        manager.add_new_message(ActionTextKeys::get_generic_wear_off_message(StringTable::get(creature->get_description_sid())));
      }

      manager.send();
    }
  }
}