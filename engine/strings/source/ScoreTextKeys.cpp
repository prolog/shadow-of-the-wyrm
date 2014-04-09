#include <boost/algorithm/string.hpp>
#include "ScoreTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

const string ScoreTextKeys::SCORE_FAREWELL_MESSAGE = "SCORE_FAREWELL_MESSAGE";

ScoreTextKeys::ScoreTextKeys()
{
}

ScoreTextKeys::~ScoreTextKeys()
{
}

string ScoreTextKeys::get_farewell_text_message(const string& name)
{
  string message = StringTable::get(SCORE_FAREWELL_MESSAGE);
  boost::replace_first(message, "%s", name);

  return message;
}