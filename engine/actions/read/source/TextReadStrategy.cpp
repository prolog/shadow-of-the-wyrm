#include "Game.hpp"
#include "SpellcastingTextKeys.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"
#include "TextReadStrategy.hpp"

using namespace std;

ActionCostValue TextReadStrategy::read(CreaturePtr creature, ActionManager * const am, ReadablePtr readable)
{
  ActionCostValue acv = 0;

  if (creature && readable)
  {
    Game& game = Game::instance();
    TextDisplayFormatter tdf;
    vector<pair<Colour, string>> book_text;
    acv = get_action_cost_value(creature);

    string text_sid = readable->get_text_sid();
    vector<string> formatted_text = tdf.format_text(StringTable::get(text_sid));

    for(const string& text_line : formatted_text)
    {
      TextDisplayPair text_line_for_ui = make_pair(COLOUR_WHITE, text_line);
      book_text.push_back(text_line_for_ui);
    }

    TextDisplayScreen tds(game.get_display(), readable->get_description_sid(), book_text);
    tds.display();
  }

  return acv;
}

pair<string, string> TextReadStrategy::get_player_and_monster_read_sids() const
{
  pair<string, string> sids(SpellcastingTextKeys::SPELLCASTING_READ_BOOK_PLAYER, SpellcastingTextKeys::SPELLCASTING_READ_BOOK_MONSTER);
  return sids;
}

ActionCostValue TextReadStrategy::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

