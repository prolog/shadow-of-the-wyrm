#include "CombatManager.hpp"
#include "Creature.hpp"
#include "Game.hpp"
#include "MessageManager.hpp"
#include "PoisonCalculator.hpp"
#include "PoisonStatusEffect.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"
#include "RNG.hpp"

using namespace std;

bool PoisonStatusEffect::should_apply_change(CreaturePtr creature) const
{
  bool creature_poisoned = false;

  if (creature && !creature->has_status(StatusIdentifiers::STATUS_ID_POISON) 
   && RNG::percent_chance(poison_calc.calculate_pct_chance_poison(creature)))
  {
    creature_poisoned = true;
  }

  return creature_poisoned;
}

void PoisonStatusEffect::apply(CreaturePtr creature) const
{
  if (creature)
  {
    Game& game = Game::instance();
    double current_seconds_since_game_start = game.get_current_world()->get_calendar().get_seconds();
    int duration = poison_calc.calculate_poison_duration_in_minutes(creature);

    StatusDuration poison_duration(current_seconds_since_game_start + (duration * 60.0));

    creature->set_status(StatusIdentifiers::STATUS_ID_POISON, true);
    creature->set_status_duration(StatusIdentifiers::STATUS_ID_POISON, poison_duration);

    string message = get_player_application_message();

    if (!message.empty() && creature->get_is_player())
    {
      MessageManager& manager = MessageManager::instance();
      manager.add_new_message(message);
      manager.send();
    }
  }
}

void PoisonStatusEffect::finalize(CreaturePtr creature) const
{
  // When poison runs its course, just remove the status ailment from
  // the creature.
  undo_change(creature);
}

void PoisonStatusEffect::undo(CreaturePtr creature) const
{
  if (creature)
  {
    creature->remove_status(StatusIdentifiers::STATUS_ID_POISON);

    if (creature->get_is_player())
    {
      MessageManager& manager = MessageManager::instance();
      manager.add_new_message(get_player_undo_message());
      manager.send();
    }
  }
}

void PoisonStatusEffect::tick(CreaturePtr creature) const
{
  CreaturePtr no_creature;
  CombatManager cm;

  // Poison always deals a single point of damage per minute.
  cm.deal_damage(no_creature, creature, poison_calc.calculate_damage_per_tick(creature));
}

string PoisonStatusEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISONED);
  return message;
}

string PoisonStatusEffect::get_player_undo_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISON_CURED);
  return message;
}

