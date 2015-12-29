#include "ExitGameAction.hpp"
#include "Game.hpp"
#include "Serialization.hpp"

using namespace std;

ExitGameAction::ExitGameAction()
{
}

ActionCostValue ExitGameAction::quit(CreaturePtr creature) const
{
  Game& game = Game::instance();
  game.stop_playing();

  return get_action_cost_value(creature);
}

ActionCostValue ExitGameAction::save(CreaturePtr creature) const
{
  Game& game = Game::instance();
  game.set_check_scores(false);

  Serialization::save(creature);
  quit(creature);

  return get_action_cost_value(creature);
}

ActionCostValue ExitGameAction::get_action_cost_value(CreaturePtr creature) const
{
  // Setting the action cost to 1 after everything has been saved/quit ensures
  // that the user doesn't have to press another key to actually quit.
  return 1;
}
