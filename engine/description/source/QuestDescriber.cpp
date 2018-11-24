#include <sstream>
#include "QuestDescriber.hpp"
#include "StringTable.hpp"

using namespace std;

QuestDescriber::QuestDescriber(const Quest& new_quest)
: quest(new_quest)
{
}

string QuestDescriber::describe() const
{
  ostringstream ss;

  string quest_title = StringTable::get(quest.get_quest_title_sid());
  vector<string> quest_title_parameter_sids = quest.get_quest_title_parameter_sids();

  for (const string& qt_param_sid : quest_title_parameter_sids)
  {
    string qt_param = StringTable::get(qt_param_sid);

    if (qt_param.empty())
    {
      qt_param = qt_param_sid;
    }

    boost::replace_first(quest_title, "%s", qt_param);
  }

  ss << quest_title;
  ss << " (" + StringTable::get(quest.get_questmaster_name_sid());
  
  string map_name = StringTable::get(quest.get_map_name_sid());
  
  if (!map_name.empty())
  {
    ss << ", " << map_name << ")";
  }

  // Most quests use a description SID, but dynamic quests have parameters
  // that need to be inserted into the string.  Insert any parameters after
  // looking up the description_sid from the resource string table.
  string quest_desc_sid = quest.get_quest_description_sid();
  string quest_description = StringTable::get(quest_desc_sid);
  vector<string> quest_desc_param_sids = quest.get_quest_description_parameter_sids();

  for (const string& param_sid : quest_desc_param_sids)
  {
    boost::replace_first(quest_description, "%s", StringTable::get(param_sid));
  }
  
  ss << ": " + quest_description;

  return ss.str();
}

