#include "WearableCodexDescriber.hpp"
#include "TextMessages.hpp"
#include "Wearable.hpp"

using namespace std;

WearableCodexDescriber::WearableCodexDescriber(ItemPtr item)
: CodexDescriber(item)
{
}

string WearableCodexDescriber::describe_speed_bonus() const
{
  WearablePtr wearable = dynamic_pointer_cast<Wearable>(item);
  string bonus;

  if (wearable != nullptr)
  {
    int speed_bonus = wearable->get_speed_bonus();

    if (speed_bonus != 0) 
    {
      bonus = TextMessages::get_speed_modifier_message(speed_bonus);
    }
  }

  return bonus;
}
