#include <boost/foreach.hpp>
#include "Game.hpp"
#include "QuestListManager.hpp"
#include "QuestDescriber.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

QuestListManager::QuestListManager()
{
}

ActionCostValue QuestListManager::quest_list() const
{
  Game& game = Game::instance();
  Quests& quests = game.get_quests_ref();
  QuestMap in_progress_quests = quests.get_in_progress_quests();

  vector<string> quests_text;

  BOOST_FOREACH(QuestMap::value_type& pair, in_progress_quests)
  {
    Quest quest = pair.second;
    QuestDescriber qd(quest);

    string long_quest_description = qd.describe();

    TextDisplayFormatter tdf;
    vector<string> current_quest_formatted = tdf.format_text(long_quest_description);

    quests_text.insert(quests_text.end(), current_quest_formatted.begin(), current_quest_formatted.end());
  }

  TextDisplayScreen tds(game.get_display(), quests_text);
  tds.display();

  return get_action_cost_value();
}

// Showing the quest list should always be a free action, since the
// player isn't actually acting in-game.
ActionCostValue QuestListManager::get_action_cost_value() const
{
  return 0;
}
