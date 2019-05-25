#include <sstream>
#include "CodexDescriber.hpp"
#include "ResistancesTranslator.hpp"
#include "ResistanceTextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

CodexDescriber::CodexDescriber(ItemPtr new_item)
: item(new_item)
{
}

string CodexDescriber::describe_for_synopsis_line() const
{
  string no_synop;
  return no_synop;
}

// Get an unabbreviated, unbraced resistances description.
string CodexDescriber::describe_resistances() const
{
  ostringstream ss;

  if (item != nullptr)
  {
    ResistancesDisplayOptions rdo(false, false);
    ResistancesTranslator rt;

    string res = rt.create_description(item->get_resistances(), rdo);

    if (!res.empty())
    {
      ss << StringTable::get(ResistanceTextKeys::RESISTANCE_RESISTANCES) << ": " << res;
    }
  }

  return ss.str();
}

string CodexDescriber::describe_details() const
{
  string no_details;
  return no_details;
}

