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
  array<bool, static_cast<size_t>(ConductType::CONDUCT_SIZE)> cond = conducts.get_conducts();
  TextDisplayPair separator = make_pair(Colour::COLOUR_WHITE, "");
  int conduct_sz = static_cast<int>(ConductType::CONDUCT_SIZE);
  vector<TextDisplayPair> conducts_unsep;

  // Get all the conducts to display
  for (int ct = static_cast<int>(ConductType::CONDUCT_TYPE_FOODLESS); ct < conduct_sz; ct++)
  {
    if (cond[ct] == true)
    {
      string msg_sid = ConductTextKeys::get_conduct_message_sid(static_cast<ConductType>(ct));
      conducts_unsep.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(msg_sid)));
    }
  }

  // Add separators after each conduct description.
  size_t cu_sz = conducts_unsep.size();
  for (size_t cu_s = 0; cu_s < cu_sz; cu_s++)
  {
    const auto& cu = conducts_unsep[cu_s];
    conducts_text.push_back(cu);

    if (cu_s != cu_sz - 1u)
    {
      conducts_text.push_back(separator);
    }
  }

  TextDisplayScreen tds(game.get_display(), cond_title_sid, conducts_text);
  tds.display();

  return get_action_cost_value(creature);
}

ActionCostValue ShowConductsAction::get_action_cost_value(CreaturePtr /* creature */) const
{
  return 0;
}
