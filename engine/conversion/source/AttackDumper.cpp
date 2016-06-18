#include <sstream>
#include "Conversion.hpp"
#include "AttackDumper.hpp"
#include "ItemDumper.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "StringTable.hpp"
#include "WeaponInfoAction.hpp"

using namespace std;

AttackDumper::AttackDumper(CreaturePtr new_creature, const uint new_num_cols)
: creature(new_creature), num_cols(new_num_cols)
{
}

string AttackDumper::str() const
{
  ostringstream ss;
  
  WeaponInfoAction wia;
  pair<string, string> wo_text = wia.get_wielded_and_offhand_text(creature);
  string ranged_text = wia.get_ranged_text(creature);

  ss << String::centre(StringTable::get(TextKeys::ATTACK_DETAILS), num_cols) << endl << endl;

  if (!wo_text.first.empty())
  {
    ss << wo_text.first << endl;
  }

  if (!wo_text.second.empty())
  {
    ss << wo_text.second << endl << endl;
  }

  if (!ranged_text.empty())
  {
    ss << ranged_text << endl << endl;
  }

  return ss.str();
}

