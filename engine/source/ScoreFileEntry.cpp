#include "ScoreFileEntry.hpp"
#include "Serialize.hpp"

using namespace std;

// Default constructor
ScoreFileEntry::ScoreFileEntry()
: score(0)
{
}

// Construct a score file entry with all required values.
ScoreFileEntry::ScoreFileEntry(const ulonglong new_score)
: score(new_score)
{
}

bool ScoreFileEntry::serialize(ostream& stream) const
{
  Serialize::write_ulonglong(stream, score);

  return true;
}

bool ScoreFileEntry::deserialize(istream& stream)
{
  Serialize::read_ulonglong(stream, score);

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

#ifdef UNIT_TESTS
#include "unit_tests/ScoreFileEntry_test.cpp"
#endif

