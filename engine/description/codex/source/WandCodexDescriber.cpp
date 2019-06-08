#include <sstream>
#include "WandCodexDescriber.hpp"
#include "ItemTextKeys.hpp"
#include "TextMessages.hpp"
#include "Wand.hpp"

using namespace std;

WandCodexDescriber::WandCodexDescriber(WandPtr new_wand)
: CodexDescriber(new_wand), wand(new_wand)
{
}

string WandCodexDescriber::describe_details() const
{
  ostringstream ss;
 
  if (wand != nullptr)
  {
    ss << ItemTextKeys::get_number_of_charges_message(wand);

    if (wand->get_has_damage())
    {
      ss << " " << TextMessages::get_damage_message(wand->get_damage());
    }
  }

  return ss.str();
}
