#include "common.hpp"
#include "Quests.hpp"
#include "Serialize.hpp"

using namespace std;

// Quest
Quest::Quest()
{
}

Quest::Quest(const string& new_id, const string& new_qtitle, const string& new_qmaster, const string& new_qdesc)
: quest_id(new_id), quest_title_sid(new_qtitle), questmaster_name_sid(new_qmaster), quest_description_sid(new_qdesc)
{
}

bool Quest::operator==(const Quest& q) const
{
  bool result = true;

  result = result && (quest_id == q.quest_id);
  result = result && (quest_title_sid == q.quest_title_sid);
  result = result && (questmaster_name_sid == q.questmaster_name_sid);
  result = result && (quest_description_sid == q.quest_description_sid);

  return result;
}

void Quest::set_quest_id(const string& new_quest_id)
{
  quest_id = new_quest_id;
}

string Quest::get_quest_id() const
{
  return quest_id;
}

void Quest::set_quest_title_sid(const string& new_quest_title_sid)
{
  quest_title_sid = new_quest_title_sid;
}

string Quest::get_quest_title_sid() const
{
  return quest_title_sid;
}

void Quest::set_questmaster_name_sid(const string& new_questmaster_name_sid)
{
  questmaster_name_sid = new_questmaster_name_sid;
}

string Quest::get_questmaster_name_sid() const
{
  return questmaster_name_sid;
}

void Quest::set_quest_description_sid(const string& new_quest_description_sid)
{
  quest_description_sid = new_quest_description_sid;
}

string Quest::get_quest_description_sid() const
{
  return quest_description_sid;
}

bool Quest::serialize(ostream& stream) const
{
  Serialize::write_string(stream, quest_id);
  Serialize::write_string(stream, quest_title_sid);
  Serialize::write_string(stream, questmaster_name_sid);
  Serialize::write_string(stream, quest_description_sid);

  return true;
}

bool Quest::deserialize(istream& stream)
{
  Serialize::read_string(stream, quest_id);
  Serialize::read_string(stream, quest_title_sid);
  Serialize::read_string(stream, questmaster_name_sid);
  Serialize::read_string(stream, quest_description_sid);

  return true;
}

ClassIdentifier Quest::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_QUEST;
}

// Quests

bool Quests::operator==(const Quests& q) const
{
  bool result = true;

  result = result && (in_progress_quest_map == q.in_progress_quest_map);
  result = result && (completed_quest_map == q.completed_quest_map);

  return result;
}

// Clear both quest maps
void Quests::clear_all_quests()
{
  in_progress_quest_map.clear();
  completed_quest_map.clear();
}

// Add a new quest to the in-progress map.
void Quests::add_new_quest(const string& quest_id, const Quest& new_quest)
{
  in_progress_quest_map[quest_id] = new_quest;
}

// Remove an active quest
bool Quests::remove_active_quest(const string& quest_id)
{
  bool quest_removed = false;

  map<string, Quest>::iterator q_it = in_progress_quest_map.find(quest_id);
  if (q_it != in_progress_quest_map.end())
  {
    in_progress_quest_map.erase(q_it);
    quest_removed = true;
  }

  return quest_removed;
}

// Check to see if the player is doing a particular quest.
bool Quests::is_quest_in_progress(const string& quest_id)
{
  return (in_progress_quest_map.find(quest_id) != in_progress_quest_map.end());
}

// Mark a quest as completed by moving it from the in-progress map into
// the completed map.
void Quests::set_quest_completed(const string& quest_id)
{
  map<string, Quest>::iterator q_it = in_progress_quest_map.find(quest_id);

  if (q_it != in_progress_quest_map.end())
  {
    Quest quest = q_it->second;

    in_progress_quest_map.erase(q_it);

    completed_quest_map[quest_id] = quest;
  }
}

// Check to see if a quest has been completed
bool Quests::is_quest_completed(const string& quest_id)
{
  return (completed_quest_map.find(quest_id) != completed_quest_map.end());
}

// Get all of the in-progress quests.
QuestMap Quests::get_in_progress_quests() const
{
  return in_progress_quest_map;
}

// Get all of the completed quests.
QuestMap Quests::get_completed_quests() const
{
  return completed_quest_map;
}

// Write out all of the in progress and completed quests.
bool Quests::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, in_progress_quest_map.size());

  for (const QuestMap::value_type& pair : in_progress_quest_map)
  {
    Serialize::write_string(stream, pair.first);
    pair.second.serialize(stream);
  }

  Serialize::write_size_t(stream, completed_quest_map.size());

  for (const QuestMap::value_type& pair : completed_quest_map)
  {
    Serialize::write_string(stream, pair.first);
    pair.second.serialize(stream);
  }

  return true;
}

// Read in all the in progress and completed quests.
bool Quests::deserialize(istream& stream)
{
  size_t inp_sizet = 0;
  Serialize::read_size_t(stream, inp_sizet);

  deserialize_quest_map(stream, inp_sizet, in_progress_quest_map);

  size_t com_sizet = 0;
  Serialize::read_size_t(stream, com_sizet);

  deserialize_quest_map(stream, com_sizet, completed_quest_map);

  return true;
}

// Deserialize an arbitrary quest map, given its size.
bool Quests::deserialize_quest_map(istream& stream, const size_t num_quests, QuestMap& quest_map)
{
  for (uint i = 0; i < num_quests; i++)
  {
    string quest_id;
    Serialize::read_string(stream, quest_id);

    Quest quest;
    quest.deserialize(stream);

    quest_map[quest_id] = quest;
  }

  return true;
}

ClassIdentifier Quests::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_QUESTS;
}

#ifdef UNIT_TESTS
#include "unit_tests/Quests_test.cpp"
#endif
