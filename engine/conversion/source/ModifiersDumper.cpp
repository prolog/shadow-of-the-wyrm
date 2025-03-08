#include <sstream>
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "DateTextKeys.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "ModifiersDumper.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "StringTable.hpp"

using namespace std;

ModifiersDumper::ModifiersDumper(CreaturePtr new_creature, const uint new_max_cols)
  : creature(new_creature), num_cols(new_max_cols)
{
}

string ModifiersDumper::str() const
{
  return get_modifiers();
}

// Get the creature's kills.
string ModifiersDumper::get_modifiers() const
{
  ostringstream ss;
  Game& game = Game::instance();
  CreatureMap cmap = game.get_creatures_ref();

  ss << String::centre(StringTable::get(TextKeys::MODIFIERS), num_cols) << endl << endl;

  if (creature != nullptr)
  {
    auto active_mods = creature->get_active_modifiers();

    if (active_mods.empty())
    {
      ss << String::centre("-", num_cols);
    }
    else
    {
      for (auto am : active_mods)
      {
        if (!am.second.empty())
        {
          for (auto am_detail : am.second)
          {
            double time_val = am.first;
            ss << "[";

            if (time_val < 0)
            {
              ss << StringTable::get(TextKeys::INDEFINITELY);
            }
            else
            {
              Calendar& calendar = game.get_current_world()->get_calendar();
              Date date = calendar.get_date(time_val);
              Date cal_date = calendar.get_date();
              ss << TextMessages::get_ending_message(DateTextKeys::get_date_time_message(date, date.get_days_equal(cal_date)));
            }

            ss << "] ";
            ss << TextMessages::get_modifier_message(am_detail.first, am_detail.second, creature) << endl << endl;
          }
        }
      }
    }

    ss << endl;
  }

  return ss.str();
}
