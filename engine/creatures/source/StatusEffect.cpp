#include "Creature.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DefaultStatusEffectCalculator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "ModifyStatisticsEffect.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"
#include "StatusEffect.hpp"

using namespace std;

StatusEffect::StatusEffect()
{
  status_calc = std::make_shared<DefaultStatusEffectCalculator>();
}

StatusEffect::~StatusEffect()
{
}

bool StatusEffect::should_apply_change(CreaturePtr creature, const int effect_bonus) const
{
  bool status_should_apply = false;

  if (creature && !creature->has_status(get_status_identifier()) 
   && RNG::percent_chance(status_calc->chance_of_effect(creature, effect_bonus)))
  {
    status_should_apply = true;
  }

  return status_should_apply;
}

void StatusEffect::apply_change(CreaturePtr creature) const
{
  bool status_applied = true;

  status_applied = before_apply(creature);
  status_applied = status_applied && apply(creature);
  status_applied = status_applied && after_apply(creature);

  if (status_applied)
  {
    string message = get_application_message(creature);

    if (!message.empty())
    {
      IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
      manager.add_new_message(message);
      manager.send();
    }
  }
}

bool StatusEffect::before_apply(CreaturePtr creature) const
{
  return true;
}

bool StatusEffect::apply(CreaturePtr creature) const
{
  if (creature)
  {
    Game& game = Game::instance();
    string status_identifier = get_status_identifier();

    double current_seconds_since_game_start = GameUtils::get_seconds(game);
    int duration = status_calc->calculate_duration_in_minutes(creature);
    double eff_dur_sec = current_seconds_since_game_start + (duration * 60);

    Modifier modifier = get_base_modifier(creature);
    modifier.set_status(status_identifier, true);

    ModifyStatisticsEffect mse;
    bool status_added = mse.apply_modifiers(creature, modifier, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_PRESET, eff_dur_sec);
  }

  return true;
}

bool StatusEffect::after_apply(CreaturePtr creature) const
{
  return true;
}

string StatusEffect::get_application_message(CreaturePtr creature) const
{
  string application_message;

  if (creature)
  {
    if (creature->get_is_player())
    {
      return get_player_application_message();
    }
    else
    {
      CurrentCreatureAbilities cca;

      if (cca.can_see(Game::instance().get_current_player()))
      {
        return get_npc_application_message(creature);
      }
      else
      {
        return "";
      }
    }
  }

  return application_message;
}

string StatusEffect::get_player_application_message() const
{
  string no_message;
  return no_message;
}

string StatusEffect::get_npc_application_message(CreaturePtr creature) const
{
  string no_message;
  return no_message;
}

void StatusEffect::finalize_change(CreaturePtr creature) const
{
  before_finalize(creature);
  finalize(creature);
  after_finalize(creature);
}

void StatusEffect::before_finalize(CreaturePtr creature) const
{
}

void StatusEffect::finalize(CreaturePtr creature) const
{
  undo_change(creature);
}

string StatusEffect::get_finalize_message(CreaturePtr creature) const
{
  string finalize_message;

  if (creature)
  {
    if (creature->get_is_player())
    {
      return get_player_finalize_message();
    }
    else
    {
      CurrentCreatureAbilities cca;

      if (cca.can_see(Game::instance().get_current_player()))
      {
        return get_npc_finalize_message(creature);
      }
      else
      {
        return "";
      }
    }
  }

  return finalize_message;
}

string StatusEffect::get_player_finalize_message() const
{
  string no_message;
  return no_message;
}

string StatusEffect::get_npc_finalize_message(CreaturePtr creature) const
{
  string no_message;
  return no_message;
}

void StatusEffect::after_finalize(CreaturePtr creature) const
{
}

void StatusEffect::undo_change(CreaturePtr creature) const
{
  before_undo(creature);
  undo(creature);
  after_undo(creature);
}

void StatusEffect::before_undo(CreaturePtr creature) const
{
}

void StatusEffect::undo(CreaturePtr creature) const
{
  if (creature)
  {
    creature->remove_status(get_status_identifier());

    IMessageManager& manager = MessageManagerFactory::instance(creature, creature->get_is_player());

    string undo_message = get_undo_message(creature);

    if (!undo_message.empty())
    {
      manager.add_new_message(undo_message);
      manager.send();
    }
  }
}

void StatusEffect::after_undo(CreaturePtr creature) const
{
}

string StatusEffect::get_undo_message(CreaturePtr creature) const
{
  string undo_message;

  if (creature)
  {
    if (creature->get_is_player())
    {
      return get_player_undo_message();
    }
    else
    {
      CurrentCreatureAbilities cca;

      if (cca.can_see(Game::instance().get_current_player()))
      {
        return get_npc_undo_message(creature);
      }
      else
      {
        return "";
      }
    }
  }

  return undo_message;
}

string StatusEffect::get_player_undo_message() const
{
  string no_message;
  return no_message;
}

string StatusEffect::get_npc_undo_message(CreaturePtr creature) const
{
  string no_message;
  return no_message;
}

void StatusEffect::tick(CreaturePtr creature) const
{
}

Modifier StatusEffect::get_base_modifier(CreaturePtr creature) const
{
  Modifier m;
  return m;
}

string StatusEffect::get_status_identifier() const
{
  string no_status_identifier;
  return no_status_identifier;
}

#ifdef UNIT_TESTS
#include "unit_tests/StatusEffect_test.cpp"
#endif
