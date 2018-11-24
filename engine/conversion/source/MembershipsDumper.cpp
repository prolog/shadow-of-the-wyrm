#include <sstream>
#include "Conversion.hpp"
#include "Game.hpp"
#include "MembershipsDumper.hpp"
#include "TextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

MembershipsDumper::MembershipsDumper(CreaturePtr new_creature, const uint new_max_cols)
: creature(new_creature), num_cols(new_max_cols)
{
}

string MembershipsDumper::str() const
{
  return get_memberships();
}

// Get the creature's current memberships
string MembershipsDumper::get_memberships() const
{
  ostringstream ss;
  int num_memberships = 0;

  ss << String::centre(StringTable::get(TextKeys::MEMBERSHIPS), num_cols) << endl << endl;

  if (creature != nullptr)
  {
    map<string, Membership> memberships = creature->get_memberships_ref().get_memberships();

    for (auto m_pair : memberships)
    {
      ss << StringTable::get(m_pair.second.get_description_sid()) << endl;
      num_memberships++;
    }
  }

  if (num_memberships == 0)
  {
    ss << String::centre("-", num_cols) << endl;
  }

  return ss.str();
}
