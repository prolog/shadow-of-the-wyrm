#include <sstream>
#include "Conversion.hpp"
#include "Game.hpp"
#include "ConductsDumper.hpp"
#include "ConductTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

ConductsDumper::ConductsDumper(CreaturePtr new_creature, const uint new_max_cols)
: creature(new_creature), num_cols(new_max_cols)
{
}

string ConductsDumper::str() const
{
  return get_conducts();
}

// Get the creature's adhered-to conducts.
string ConductsDumper::get_conducts() const
{
  ostringstream ss;

  ss << String::centre(StringTable::get(ConductTextKeys::CONDUCT_TITLE), num_cols) << endl << endl;
  Conducts cond = creature->get_conducts_ref();

  array<bool, CONDUCT_SIZE> all_cond = cond.get_conducts();
  int num_conducts = 0;

  for (uint i = 0; i < all_cond.size(); i++)
  {
    bool cur_cond = all_cond.at(i);

    if (cur_cond == true)
    {
      string conduct_desc = StringTable::get(ConductTextKeys::get_conduct_message_sid(static_cast<ConductType>(i)));
      ss << conduct_desc << endl;
      num_conducts++;
    }
  }

  if (num_conducts == 0)
  {
    ss << String::centre("-", num_cols) << endl;
  }

  return ss.str();
}
