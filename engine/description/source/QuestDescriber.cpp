#include "QuestDescriber.hpp"
#include "StringTable.hpp"

using std::string;

QuestDescriber::QuestDescriber(const Quest& new_quest)
: quest(new_quest)
{
}

string QuestDescriber::describe() const
{
  string description;

  description = StringTable::get(quest.get_quest_title_sid());
  description += " (" + StringTable::get(quest.get_questmaster_name_sid()) + ")";
  description += ": " + StringTable::get(quest.get_quest_description_sid());

  return description;
}

