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

  ss << StringTable::get(quest.get_quest_title_sid());
  ss << " (" + StringTable::get(quest.get_questmaster_name_sid());
  
  string map_name = StringTable::get(quest.get_map_name_sid());
  
  if (!map_name.empty())
  {
    ss << ", " << map_name << ")";
  }

  ss << ": " + StringTable::get(quest.get_quest_description_sid());

  return ss.str();
}

