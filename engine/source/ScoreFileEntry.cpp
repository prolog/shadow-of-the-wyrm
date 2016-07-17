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
: score(0), sex(CreatureSex::CREATURE_SEX_MALE), is_current_char(false), level(0), winner(CreatureWin::CREATURE_WIN_NO_WIN)
{
}

// Construct a score file entry with all required values.
ScoreFileEntry::ScoreFileEntry(const long long new_score, const string& new_name, const string& new_username, const CreatureSex new_sex, const bool new_is_current_char, const int new_level, const CreatureWin new_winner, const string& new_race_class_abrv)
: score(new_score), name(new_name), username(new_username), sex(new_sex), is_current_char(new_is_current_char), level(new_level), winner(new_winner), race_class_abrv(new_race_class_abrv)
{
}

bool ScoreFileEntry::operator<(const ScoreFileEntry& sfe) const
{
  return (score < sfe.get_score());
}

bool ScoreFileEntry::serialize(ostream& stream) const
{
  Serialize::write_longlong(stream, score);
  Serialize::write_string(stream, name);
  Serialize::write_string(stream, username);
  Serialize::write_enum(stream, sex);

  // The constant below is "is_current_char".  After writing the entry to
  // disk, the entry will never again reference the current character, so
  // a value of false is always correct.
  Serialize::write_bool(stream, false);
  
  Serialize::write_int(stream, level);
  Serialize::write_enum(stream, winner);
  Serialize::write_string(stream, race_class_abrv);

  return true;
}

bool ScoreFileEntry::deserialize(istream& stream)
{
  Serialize::read_longlong(stream, score);
  Serialize::read_string(stream, name);
  Serialize::read_string(stream, username);
  Serialize::read_enum(stream, sex);
  Serialize::read_bool(stream, is_current_char);
  Serialize::read_int(stream, level);
  Serialize::read_enum(stream, winner);
  Serialize::read_string(stream, race_class_abrv);

  return true;
}

ClassIdentifier ScoreFileEntry::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_SCORE_FILE_ENTRY;
}

long long ScoreFileEntry::get_score() const
{
  return score;
}

string ScoreFileEntry::get_name() const
{
  return name;
}

string ScoreFileEntry::get_username() const
{
  return username;
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

CreatureWin ScoreFileEntry::get_winner() const
{
  return winner;
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

  ss << score_number << ". " << get_score() << ". " << get_name() << " (" << get_username() << ") - " << StringTable::get(TextKeys::LEVEL_ABRV) << get_level() << " " << rc_abrv << " (" << TextMessages::get_sex_abrv(get_sex()) << ").";

  switch (winner)
  {
    case CreatureWin::CREATURE_WIN_REGULAR:
      ss << " " << StringTable::get(TextKeys::WINNER) << "!";
      break;
    case CreatureWin::CREATURE_WIN_EVIL:
      ss << " " << StringTable::get(TextKeys::WINNER_EVIL) << "!";
      break;
    case CreatureWin::CREATURE_WIN_NO_WIN:
    default:
      break;
  }

  return ss.str();
}

#ifdef UNIT_TESTS
#include "unit_tests/ScoreFileEntry_test.cpp"
#endif

