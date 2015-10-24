#include <sstream>
#include "Conversion.hpp"
#include "Game.hpp"
#include "ResistancesDumper.hpp"
#include "ResistanceTextKeys.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "StringTable.hpp"
#include "TextKeys.hpp"

using namespace std;

ResistancesDumper::ResistancesDumper(CreaturePtr new_creature, const uint new_max_cols)
: creature(new_creature), num_cols(new_max_cols)
{
}

string ResistancesDumper::str() const
{
  return get_resistances();
}

// Get the creature's resistances.
string ResistancesDumper::get_resistances() const
{
  ostringstream ss;

  ss << String::centre(StringTable::get(ScreenTitleTextKeys::SCREEN_TITLE_RESISTANCES), num_cols) << endl << endl;

  Resistances res = creature->get_resistances();

  for (int d = static_cast<int>(DamageType::DAMAGE_TYPE_FIRST); d < static_cast<int>(DamageType::DAMAGE_TYPE_MAX); d++)
  {
    DamageType dt = static_cast<DamageType>(d);

    ResistancePtr cur_res = res.get_resistance(dt);
    double res_val = cur_res->get_value();
    string name_sid = cur_res->get_name_sid();

    ss << StringTable::get(name_sid) << ": " << res_val << endl;
  }

  return ss.str();
}
