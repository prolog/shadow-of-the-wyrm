#include <vector>
#include "Game.hpp"
#include "ResistanceTextKeys.hpp"
#include "ShowResistancesAction.hpp"
#include <iomanip>
#include "TextDisplayScreen.hpp"

using namespace std;

ActionCostValue ShowResistancesAction::show_resistances(CreaturePtr creature)
{
  Game& game = Game::instance();
  string resistances_title_sid = ResistanceTextKeys::RESISTANCES_SCREEN_TITLE;
  vector<TextDisplayPair> resists_text;

  Resistances res = creature->get_resistances();
  TextDisplayPair separator = make_pair(COLOUR_WHITE, "");

  resists_text.push_back(make_pair(COLOUR_WHITE, StringTable::get(ResistanceTextKeys::RESISTANCES_EXPLANATION)));
  resists_text.push_back(separator);

  for (DamageType dt = DAMAGE_TYPE_FIRST; dt < DAMAGE_TYPE_MAX; dt++)
  {
    ostringstream ss;
    ResistancePtr cur_res = res.get_resistance(dt);
    double res_val = cur_res->get_value();
    string name = cur_res->get_name_sid();
    Colour text_colour = get_resistance_text_colour(res_val);

    ss << StringTable::get(name) << ": " << res_val;

    TextDisplayPair resistance_info = make_pair(text_colour, ss.str());
    resists_text.push_back(resistance_info);
  }

  TextDisplayScreen tds(game.get_display(), resistances_title_sid, resists_text);
  tds.display();

  return get_action_cost_value(creature);
}

// Resists should be green, vulnerabilities red, "normal" white.
Colour ShowResistancesAction::get_resistance_text_colour(const double resist_value)
{
  // Base (value = 1)
  Colour text_colour = COLOUR_WHITE;

  // Vuln
  if (resist_value > 1)
  {
    text_colour = COLOUR_BOLD_RED;
  }
  // Resist
  else if (resist_value < 1)
  {
    text_colour = COLOUR_BOLD_GREEN;
  }

  return text_colour;
}
ActionCostValue ShowResistancesAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}
