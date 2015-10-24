#include <sstream>
#include "Conversion.hpp"
#include "Game.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "QuestDescriber.hpp"
#include "QuestDumper.hpp"
#include "TextDisplayFormatter.hpp"
#include "StringTable.hpp"

using namespace std;

QuestDumper::QuestDumper(CreaturePtr new_creature, const uint new_max_cols)
: creature(new_creature), num_cols(new_max_cols)
{
}

string QuestDumper::str() const
{
  return get_quests();
}

// Get the creature's quest.
string QuestDumper::get_quests() const
{
  ostringstream ss;

  if (creature->get_is_player())
  {
    Game& game = Game::instance();
    Quests& quests = game.get_quests_ref();
    QuestMap in_progress_quests = quests.get_in_progress_quests();
    ss << String::centre(StringTable::get(ScreenTitleTextKeys::SCREEN_TITLE_QUEST_LIST), num_cols) << endl << endl;
   
    int num_in_progress = 0;

    for (const auto& pair : in_progress_quests)
    {
      Quest quest = pair.second;
      dump_quest(ss, quest);
      num_in_progress++;
    }

    if (num_in_progress == 0)
    {
      ss << String::centre("-", num_cols);
    }

    ss << endl << endl;

    QuestMap completed_quests = quests.get_completed_quests();
    ss << String::centre(StringTable::get(ScreenTitleTextKeys::SCREEN_TITLE_COMPLETED_QUEST_LIST), num_cols) << endl << endl;

    int num_completed = 0;

    for (const auto& pair : completed_quests)
    {
      Quest quest = pair.second;
      dump_quest(ss, quest);
      num_completed++;
    }

    if (num_completed == 0)
    {
      ss << String::centre("-", num_cols);
    }
  }

  return ss.str();
}

void QuestDumper::dump_quest(ostream& stream, const Quest& quest) const
{
  QuestDescriber qd(quest);

  string long_quest_description = qd.describe();

  TextDisplayFormatter tdf;
  vector<string> current_quest_formatted = tdf.format_text(long_quest_description);

  for (const string& quest_line : current_quest_formatted)
  {
    stream << quest_line << endl;
  }

  stream << endl;
}