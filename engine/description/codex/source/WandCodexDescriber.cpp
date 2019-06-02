#include <sstream>
#include "WandCodexDescriber.hpp"
#include "ItemTextKeys.hpp"
#include "TextMessages.hpp"
#include "Wand.hpp"

using namespace std;

WandCodexDescriber::WandCodexDescriber(ItemPtr item)
: CodexDescriber(item)
{
}

string WandCodexDescriber::describe_details() const
{
  ostringstream ss;
  WandPtr wand = dynamic_pointer_cast<Wand>(item);

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
