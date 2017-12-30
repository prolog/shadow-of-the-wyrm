#include "Creature.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "DefaultStatusEffectCalculator.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "ModifyStatisticsEffect.hpp"
#include "RNG.hpp"
#include "Serialize.hpp"
#include "StatisticsMarker.hpp"
#include "StatusEffect.hpp"

using namespace std;

StatusEffect::StatusEffect()
{
  status_calc = std::make_shared<DefaultStatusEffectCalculator>();
}

StatusEffect::StatusEffect(const string& new_source_id)
: source_id(new_source_id)
{
}

StatusEffect::~StatusEffect()
{
}

// Most status effects are negative.
bool StatusEffect::is_negative() const
{
  return true;
}

void StatusEffect::set_source_id(const string& new_source_id)
{
  source_id = new_source_id;
}

string StatusEffect::get_source_id() const
{
  return source_id;
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

void StatusEffect::apply_change(CreaturePtr creature, const int danger_level) const
{
  bool status_applied = true;

  status_applied = before_apply(creature);
  status_applied = status_applied && apply(creature, danger_level);
  status_applied = status_applied && after_apply(creature);

  if (status_applied)
  {
    string message = get_application_message(creature);

    if (!message.empty())
    {
      IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
      manager.add_new_message(message);
      manager.send();
    }
  }
}

bool StatusEffect::before_apply(CreaturePtr creature) const
{
  return true;
}

bool StatusEffect::apply(CreaturePtr creature, const int danger_level) const
{
  if (creature)
  {
    Game& game = Game::instance();
    string status_identifier = get_status_identifier();

    double current_seconds_since_game_start = GameUtils::get_seconds(game);
    int duration = status_calc->calculate_duration_in_minutes(creature);
    double eff_dur_sec = 0;

    // Some status calculators (hiding, etc) will return max int.  This
    // indicates that the effect should be turn-based, or indefinite,
    // and will be cancelled by some other mechanism.
    if (duration < std::numeric_limits<int>::max())
    {
      eff_dur_sec = current_seconds_since_game_start + (duration * 60);
    }
    else
    {
      eff_dur_sec = std::numeric_limits<double>::max();
    }

    Modifier modifier = get_base_modifier(creature, danger_level);
    modifier.set_status(status_identifier, true, danger_level);

    ModifyStatisticsEffect mse;
    mse.set_source_id(source_id);
    mse.set_spell_id(status_identifier);
    mse.apply_modifiers(creature, modifier, ModifyStatisticsDuration::MODIFY_STATISTICS_DURATION_PRESET, eff_dur_sec);
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
    CreatureUtils::mark_modifiers_for_deletion(creature, get_status_identifier(), StatusRemovalType::STATUS_REMOVAL_UNDO);

    IMessageManager& manager = MM::instance(MessageTransmit::FOV, creature, creature->get_is_player());

    string undo_message = get_undo_message(creature);

    if (!undo_message.empty())
    {
      manager.add_new_message(undo_message);
      manager.send();
    }

    // When a creature has dealt with a particular status, whether harmful or
    // beneficial, they are the stronger for it.
    StatisticsMarker sm;
    sm.mark_health(creature);
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

void StatusEffect::tick(CreaturePtr creature, const int danger_level) const
{
}

Modifier StatusEffect::get_base_modifier(CreaturePtr creature, const int danger_level) const
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
