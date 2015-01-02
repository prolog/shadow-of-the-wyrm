#include "Game.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "QuestListAction.hpp"
#include "QuestDescriber.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

QuestListAction::QuestListAction()
{
}

ActionCostValue QuestListAction::quest_list() const
{
  Game& game = Game::instance();
  Quests& quests = game.get_quests_ref();
  QuestMap in_progress_quests = quests.get_in_progress_quests();

  string quest_title_sid = ScreenTitleKeys::SCREEN_TITLE_QUEST_LIST;
  vector<pair<Colour, string>> quests_text;
  string separator; // an empty line of text used to separate quests in the list.

  for(const QuestMap::value_type& pair : in_progress_quests)
  {
    Quest quest = pair.second;
    QuestDescriber qd(quest);

    string long_quest_description = qd.describe();

    TextDisplayFormatter tdf;
    vector<string> current_quest_formatted = tdf.format_text(long_quest_description);
    current_quest_formatted.push_back(separator);

    for(const string& quest_line : current_quest_formatted)
    {
      TextDisplayPair quest_line_for_ui = make_pair(Colour::COLOUR_WHITE, quest_line);
      quests_text.push_back(quest_line_for_ui);
    }
  }

  TextDisplayScreen tds(game.get_display(), quest_title_sid, quests_text);
  tds.display();

  CreaturePtr nullc;
  return get_action_cost_value(nullc);
}

// Showing the quest list should always be a free action, since the
// player isn't actually acting in-game.
ActionCostValue QuestListAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}
