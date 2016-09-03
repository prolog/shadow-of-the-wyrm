#include <sstream>
#include <vector>
#include <iomanip>
#include "Game.hpp"
#include "ResistanceTextKeys.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "ShowResistancesAction.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

ActionCostValue ShowResistancesAction::show_resistances(CreaturePtr creature)
{
  Game& game = Game::instance();
  string resistances_title_sid = ScreenTitleTextKeys::SCREEN_TITLE_RESISTANCES;
  vector<TextDisplayPair> resists_text;

  Resistances res = creature->get_resistances();
  TextDisplayPair separator = make_pair(Colour::COLOUR_WHITE, "");

  resists_text.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(ResistanceTextKeys::RESISTANCES_EXPLANATION)));
  resists_text.push_back(separator);
  
  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);
    ostringstream ss;
    
    ResistancePtr cur_res = res.get_resistance(dt);
    double res_val = cur_res->get_value();
    string res_str = cur_res->get_value_str();
    string name = cur_res->get_name_sid();
    Colour text_colour = get_resistance_text_colour(res_val);

    ss << StringTable::get(name) << ": " << res_str;

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
  Colour text_colour = Colour::COLOUR_WHITE;

  // Vuln
  if (resist_value > 1)
  {
    text_colour = Colour::COLOUR_BOLD_RED;
  }
  // Resist
  else if (resist_value < 1)
  {
    text_colour = Colour::COLOUR_BOLD_GREEN;
  }

  return text_colour;
}
ActionCostValue ShowResistancesAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}
