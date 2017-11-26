#include <sstream>
#include "Conversion.hpp"
#include "StringTable.hpp"
#include "VictoryDumper.hpp"
#include "VictoryTextKeys.hpp"

using namespace std;

VictoryDumper::VictoryDumper(CreaturePtr new_creature, const uint new_max_cols)
: creature(new_creature), num_cols(new_max_cols)
{
}

string VictoryDumper::str() const
{
  return get_wins();
}

string VictoryDumper::get_wins() const
{
  ostringstream ss;

  if (creature != nullptr)
  {
    vector<CreatureWin> wins = creature->get_satisfied_win_conditions();

    if (!wins.empty())
    {
      // Add a header
      ss << String::centre(StringTable::get(VictoryTextKeys::VICTORY), num_cols) << endl << endl;

      for (const CreatureWin win : wins)
      {
        string cur_vic_key = VictoryTextKeys::VICTORY + "_" + to_string(static_cast<int>(win));
        string victory_text = StringTable::get(cur_vic_key);
        
        ss << victory_text << endl;
      }
    }
  }

  return ss.str();
}
