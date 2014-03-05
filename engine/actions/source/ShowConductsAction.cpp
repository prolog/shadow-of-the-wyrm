#include <vector>
#include "Game.hpp"
#include "ConductTextKeys.hpp"
#include "ShowConductsAction.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

ActionCostValue ShowConductsAction::show_conducts(CreaturePtr creature)
{
  Game& game = Game::instance();
  string cond_title_sid = ConductTextKeys::CONDUCT_TITLE;
  vector<TextDisplayPair> conducts_text;

  Conducts& conducts = creature->get_conducts_ref();
  array<bool, CONDUCT_SIZE> cond = conducts.get_conducts();
  TextDisplayPair separator = make_pair(COLOUR_WHITE, "");

  for (int ct = CONDUCT_TYPE_FOODLESS; ct < CONDUCT_SIZE; ct++)
  {
    if (cond[ct] == true)
    {
      string msg_sid = ConductTextKeys::get_conduct_message_sid(static_cast<ConductType>(ct));
      conducts_text.push_back(make_pair(COLOUR_WHITE, StringTable::get(msg_sid)));
      conducts_text.push_back(separator);
    }
  }

  TextDisplayScreen tds(game.get_display(), cond_title_sid, conducts_text);
  tds.display();

  return get_action_cost_value(creature);
}

ActionCostValue ShowConductsAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}
