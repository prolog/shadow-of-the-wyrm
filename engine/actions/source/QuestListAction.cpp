#include <boost/foreach.hpp>
#include "Game.hpp"
#include "MenuTitleTextKeys.hpp"
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

  string quest_title_sid = MenuTitleKeys::MENU_TITLE_QUEST_LIST;
  vector<string> quests_text;
  string separator; // an empty line of text used to separate quests in the list.

  BOOST_FOREACH(QuestMap::value_type& pair, in_progress_quests)
  {
    Quest quest = pair.second;
    QuestDescriber qd(quest);

    string long_quest_description = qd.describe();

    TextDisplayFormatter tdf;
    vector<string> current_quest_formatted = tdf.format_text(long_quest_description);
    current_quest_formatted.push_back(separator);

    quests_text.insert(quests_text.end(), current_quest_formatted.begin(), current_quest_formatted.end());
  }

  TextDisplayScreen tds(game.get_display(), quest_title_sid, quests_text);
  tds.display();

  return get_action_cost_value();
}

// Showing the quest list should always be a free action, since the
// player isn't actually acting in-game.
ActionCostValue QuestListAction::get_action_cost_value() const
{
  return 0;
}
