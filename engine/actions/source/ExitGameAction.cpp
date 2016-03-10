#include "ExitGameAction.hpp"
#include "CharacterAction.hpp"
#include "EffectFactory.hpp"
#include "Game.hpp"
#include "Serialization.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"

using namespace std;

ExitGameAction::ExitGameAction()
{
}

ActionCostValue ExitGameAction::quit(CreaturePtr creature, const bool show_quit_actions) const
{
  Game& game = Game::instance();
  game.stop_playing(creature, show_quit_actions, true);

  return get_action_cost_value(creature);
}

ActionCostValue ExitGameAction::save(CreaturePtr creature) const
{
  Game& game = Game::instance();
  game.set_check_scores(false);

  Serialization::save(creature);
  quit(creature, false);

  return get_action_cost_value(creature);
}

ActionCostValue ExitGameAction::get_action_cost_value(CreaturePtr creature) const
{
  // Setting the action cost to 1 after everything has been saved/quit ensures
  // that the user doesn't have to press another key to actually quit.
  return 1;
}

void ExitGameAction::create_dump_if_necessary(IMessageManager& manager, ActionManager * const am, CreaturePtr creature) const
{
  manager.add_new_confirmation_message(TextMessages::get_confirmation_message(TextKeys::DECISION_CREATE_IDENTIFIED_DUMP));
  bool create_dump = creature && creature->get_decision_strategy()->get_confirmation();

  if (create_dump)
  {
    EffectPtr identify = EffectFactory::create_effect(EffectType::EFFECT_TYPE_IDENTIFY);

    if (identify != nullptr)
    {
      identify->effect(creature, am, ItemStatus::ITEM_STATUS_BLESSED, false);
    }

    CharacterAction ca;
    ca.dump_character(creature);
  }
}