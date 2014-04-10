#include "ScoreFileEntry.hpp"
#include "Serialize.hpp"

using namespace std;

// Default constructor
ScoreFileEntry::ScoreFileEntry()
: score(0)
{
}

// Construct a score file entry with all required values.
ScoreFileEntry::ScoreFileEntry(const ulonglong new_score, const string& new_name, const int new_level, const string& new_race_class_abrv)
: score(new_score), name(new_name), level(new_level), race_class_abrv(new_race_class_abrv)
{
}

bool ScoreFileEntry::operator<(const ScoreFileEntry& sfe) const
{
  return (score < sfe.get_score());
}

bool ScoreFileEntry::serialize(ostream& stream) const
{
  Serialize::write_ulonglong(stream, score);
  Serialize::write_string(stream, name);
  Serialize::write_int(stream, level);
  Serialize::write_string(stream, race_class_abrv);

  return true;
}

bool ScoreFileEntry::deserialize(istream& stream)
{
  Serialize::read_ulonglong(stream, score);
  Serialize::read_string(stream, name);
  Serialize::read_int(stream, level);
  Serialize::read_string(stream, race_class_abrv);

  return true;
}

ClassIdentifier ScoreFileEntry::internal_class_identifier() const
{
  return CLASS_ID_SCORE_FILE_ENTRY;
}

ulonglong ScoreFileEntry::get_score() const
{
  return score;
}

string ScoreFileEntry::get_name() const
{
  return name;
}

int ScoreFileEntry::get_level() const
{
  return level;
}

string ScoreFileEntry::get_race_class_abrv() const
{
  return race_class_abrv;
}

#ifdef UNIT_TESTS
#include "unit_tests/ScoreFileEntry_test.cpp"
#endif

