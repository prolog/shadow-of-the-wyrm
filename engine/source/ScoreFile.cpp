#include <boost/algorithm/string.hpp>
#include <boost/filesystem.hpp>
#include "CompilationDetails.hpp"
#include "Conversion.hpp"
#include "CreatureUtils.hpp"
#include "HighScoreConstants.hpp"
#include "Metadata.hpp"
#include "ScoreCalculator.hpp"
#include "ScoreFile.hpp"
#include "Serialize.hpp"

using namespace std;
using namespace boost::algorithm;

// Read the score file into the internal data structure - throw an exception
// if the file can't be read.
ScoreFile::ScoreFile()
{
  read_score_file();
}

// Generally, this constructor should only be used e.g. for unit tests where we
// don't care about the actual score file, just the class functionality.
ScoreFile::ScoreFile(const bool read_sf)
{
  if (read_sf)
  {
    read_score_file();
  }
}

void ScoreFile::read_score_file()
{
  ifstream score_file(HighScoreConstants::FILENAME);

  if (boost::filesystem::exists(HighScoreConstants::FILENAME))
  {
    ifstream score_file;

    score_file.open(HighScoreConstants::FILENAME, ios_base::binary);

    if (!(score_file.is_open() && score_file.good()))
    {
      throw std::runtime_error("Problem opening existing score file.");
    }
    else
    {
      bool read_ok = read_file(score_file);
      if (!read_ok) throw std::runtime_error("Exception while reading the score file.");
    }
  }
}

void ScoreFile::save()
{
  CompilationDetails cd;

  string version = cd.get_compilation_details_string();
  ofstream score_file;

  score_file.open(HighScoreConstants::FILENAME, ios::binary);

  if (!score_file.good())
  {
    throw std::runtime_error("Could not write high score file!");
  }

  // Write the version.
  Serialize::write_string(score_file, version);

  // How many entries?
  size_t num_entries = std::min(HighScoreConstants::MAX_ENTRIES, entries.size());
  Serialize::write_size_t(score_file, num_entries);

  // Write out the entries.
  size_t cur_count = 0;
  for (const auto& score_entry : entries)
  {
    if (cur_count < num_entries)
    {
      score_entry.serialize(score_file);
    }
    else
    {
      break;
    }
  }
}

bool ScoreFile::version_ok(istream& stream)
{
  CompilationDetails cd;
  string version;
  Serialize::read_string(stream, version);

  return (version == cd.get_compilation_details_string());
}

vector<ScoreFileEntry> ScoreFile::get_entries() const
{
  return entries;
}

// Check to see if the score file has the maximum number of entries.
bool ScoreFile::is_full() const
{
  return (entries.size() >= HighScoreConstants::MAX_ENTRIES);
}

bool ScoreFile::read_file(istream& score_file)
{
  // Sanity check - version ok?
  if (!version_ok(score_file))
  {
    throw std::runtime_error("Score file version does not match game version - please remove!");
  }

  // Read in the score file.

  // How many entries?
  size_t cur_entry = 0;
  size_t num_entries = 0;
  Serialize::read_size_t(score_file, num_entries);

  // Read in all the entries.
  while (cur_entry < num_entries)
  {
    ScoreFileEntry sfe;

    sfe.deserialize(score_file);
    entries.push_back(sfe);

    cur_entry++;
  }

  return score_file.good();
}

// Write out the creature to the score file's data structure.
// Return true if the creature was added, false if it wasn't.
bool ScoreFile::write(CreaturePtr creature)
{
  bool result = false;

  if (creature != nullptr)
  {
    ScoreCalculator sc;

    long long cr_score = sc.calculate_score(creature);
    bool sf_full = is_full();

    // We can write to the score file if one of the following is true:
    // - There are no entries
    // - The score file is not full
    // - The score file is full, but the current creature's score is greater
    //   than that of the last entry (in this case, after writing the entry
    //   and re-sorting, drop the last element).
    if (entries.empty() || !sf_full || (sf_full && cr_score > entries.back().get_score()))
    {
      Metadata m;

      ScoreFileEntry sfe(cr_score, creature->get_name(), m.get_user_name(), creature->get_sex(), creature->get_is_player(), creature->get_level().get_current(), CreatureUtils::get_race_class_synopsis(creature));
      entries.push_back(sfe);

      // Sort descending.
      sort(entries.rbegin(), entries.rend());

      if (entries.size() > HighScoreConstants::MAX_ENTRIES)
      {
        // We've gone over the limit - remove the last item.
        entries.pop_back();
      }
    }

    result = true;
  }

  return result;
}
