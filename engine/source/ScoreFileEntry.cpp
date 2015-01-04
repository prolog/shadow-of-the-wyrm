#include <boost/algorithm/string.hpp>
#include "Conversion.hpp"
#include "ScoreFileEntry.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"

using namespace std;

// Default constructor
ScoreFileEntry::ScoreFileEntry()
: score(0), sex(CreatureSex::CREATURE_SEX_MALE), is_current_char(false), level(0)
{
}

// Construct a score file entry with all required values.
ScoreFileEntry::ScoreFileEntry(const ulonglong new_score, const string& new_name, const CreatureSex new_sex, const bool new_is_current_char, const int new_level, const string& new_race_class_abrv)
: score(new_score), name(new_name), sex(new_sex), is_current_char(new_is_current_char), level(new_level), race_class_abrv(new_race_class_abrv)
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
  Serialize::write_enum(stream, sex);

  // The constant below is "is_current_char".  After writing the entry to
  // disk, the entry will never again reference the current character, so
  // a value of false is always correct.
  Serialize::write_bool(stream, false);
  
  Serialize::write_int(stream, level);
  Serialize::write_string(stream, race_class_abrv);

  return true;
}

bool ScoreFileEntry::deserialize(istream& stream)
{
  Serialize::read_ulonglong(stream, score);
  Serialize::read_string(stream, name);
  Serialize::read_enum(stream, sex);
  Serialize::read_bool(stream, is_current_char);
  Serialize::read_int(stream, level);
  Serialize::read_string(stream, race_class_abrv);

  return true;
}

ClassIdentifier ScoreFileEntry::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SCORE_FILE_ENTRY;
}

ulonglong ScoreFileEntry::get_score() const
{
  return score;
}

string ScoreFileEntry::get_name() const
{
  return name;
}

CreatureSex ScoreFileEntry::get_sex() const
{
  return sex;
}

bool ScoreFileEntry::get_is_current_char() const
{
  return is_current_char;
}

int ScoreFileEntry::get_level() const
{
  return level;
}

string ScoreFileEntry::get_race_class_abrv() const
{
  return race_class_abrv;
}

string ScoreFileEntry::str(const int score_number) const
{
  ostringstream ss;
  string rc_abrv = get_race_class_abrv();
  boost::algorithm::trim(rc_abrv);

  ss << score_number << ". " << get_score() << ". " << get_name() << " - " << StringTable::get(TextKeys::LEVEL_ABRV) << get_level() << " " << rc_abrv << " (" << TextMessages::get_sex_abrv(get_sex()) << ").";
  return ss.str();
}

#ifdef UNIT_TESTS
#include "unit_tests/ScoreFileEntry_test.cpp"
#endif

