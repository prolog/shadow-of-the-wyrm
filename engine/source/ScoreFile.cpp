#include <boost/filesystem.hpp>
#include "CompilationDetails.hpp"
#include "CreatureUtils.hpp"
#include "HighScoreConstants.hpp"
#include "ScoreCalculator.hpp"
#include "ScoreFile.hpp"
#include "ScoreTextKeys.hpp"
#include "Serialize.hpp"

using namespace std;

// Read the score file into the internal data structure - throw an exception
// if the file can't be read.
ScoreFile::ScoreFile()
{
  ifstream score_file(HighScoreConstants::FILENAME);

  if (boost::filesystem::exists(HighScoreConstants::FILENAME)) 
  {
    ifstream score_file;

    score_file.open(HighScoreConstants::FILENAME, ios_base::in | ios_base::binary);

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

ScoreFile::~ScoreFile()
{
  CompilationDetails cd;

  string version = cd.get_compilation_details_string();
  ofstream score_file;

  score_file.open(HighScoreConstants::FILENAME, ios::out, ios::binary);

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
      score_entry.second.serialize(score_file);
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
    entries.insert(make_pair(sfe.get_score(), sfe));

    cur_entry++;
  }

  return score_file.good();
}

// Write out the creature to the score file - return true if the creature
// was written, false otherwise.
bool ScoreFile::write(CreaturePtr creature)
{
  bool result = false;

  if (creature != nullptr)
  {
    auto r_iter = entries.rbegin();
    ScoreCalculator sc;

    ulonglong cr_score = sc.calculate_score(creature);

    if (entries.empty() || (cr_score > r_iter->first))
    {
      ScoreFileEntry sfe(cr_score, creature->get_name(), CreatureUtils::get_race_class_synopsis(creature));
      entries.insert(make_pair(cr_score, sfe));

      if (entries.size() > HighScoreConstants::MAX_ENTRIES)
      {
        // We've gone over the limit - remove the last item.
        entries.erase(boost::prior(entries.end()));
      }
    }

    result = true;
  }

  return result;
}

// Get the scores surrounding a particular creature.
string ScoreFile::str(CreaturePtr creature) const
{
  ostringstream ss;

  ss << ScoreTextKeys::get_farewell_text_message(creature->get_name());

  return ss.str();
}