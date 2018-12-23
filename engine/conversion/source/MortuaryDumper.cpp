#include <sstream>
#include "Conversion.hpp"
#include "ExperienceManager.hpp"
#include "Game.hpp"
#include "MortuaryDumper.hpp"
#include "TextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

MortuaryDumper::MortuaryDumper(CreaturePtr new_creature, const uint new_max_cols)
: creature(new_creature), num_cols(new_max_cols)
{
}

string MortuaryDumper::str() const
{
  return get_mortuary();
}

// Get the creature's kills.
string MortuaryDumper::get_mortuary() const
{
  ostringstream ss;

  ss << String::centre(StringTable::get(TextKeys::MORTUARY), num_cols) << endl << endl;

  Mortuary& mortuary = creature->get_mortuary_ref();
  MortuaryCountMap mcm = mortuary.get_creatures_killed();
  Game& game = Game::instance();
  CreatureMap cmap = game.get_creatures_ref();

  for (auto mcm_vt : mcm)
  {
    string creature_id = mcm_vt.first;    
    int count = mcm_vt.second.count;
    string short_desc_sid = mcm_vt.second.short_desc_sid;
    ss << StringTable::get(short_desc_sid) << ": " << count << endl;
  }

  ss << endl << StringTable::get(TextKeys::TOTAL) << ": " << mortuary.get_num_creatures_killed() << endl;

  pair<int, string> max_level_diff = mortuary.get_max_level_difference();
  string creature_id = max_level_diff.second;

  if (!creature_id.empty())
  {
    ss << StringTable::get(TextKeys::MAXIMUM_LEVEL_DIFFERENCE) << ": " << max_level_diff.first;
    auto m_it = cmap.find(creature_id);

    if (m_it != cmap.end())
    {
      ss << " (" << StringTable::get(m_it->second->get_short_description_sid()) << ")" << endl;
    }
  }

  return ss.str();
}
