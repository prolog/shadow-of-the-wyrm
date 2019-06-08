#include "WearableCodexDescriber.hpp"
#include "ItemTextKeys.hpp"
#include "Wearable.hpp"

using namespace std;

WearableCodexDescriber::WearableCodexDescriber(WearablePtr new_wearable)
: CodexDescriber(new_wearable), always_describe_protect(false), wearable(new_wearable)
{
}

WearableCodexDescriber::WearableCodexDescriber(WearablePtr new_wearable, const bool new_always_describe_protect)
: CodexDescriber(new_wearable), always_describe_protect(new_always_describe_protect), wearable(new_wearable)
{
}

string WearableCodexDescriber::describe_speed_bonus() const
{
  string bonus;

  if (wearable != nullptr)
  {
    int speed_bonus = wearable->get_speed_bonus();

    if (speed_bonus != 0) 
    {
      bonus = ItemTextKeys::get_speed_modifier_message(speed_bonus);
    }
  }

  return bonus;
}

string WearableCodexDescriber::describe_details() const
{
  string details;

  if (wearable != nullptr)
  {
    int evade = wearable->get_evade();
    int soak = wearable->get_soak();

    if (!(evade == 0 && soak == 0) || always_describe_protect)
    {
      details = ItemTextKeys::get_wearable_protection_message(evade, soak);
    }
  }

  return details;
}

void WearableCodexDescriber::set_always_describe_protect(const bool new_always_describe_protect)
{
  always_describe_protect = new_always_describe_protect;
}

bool WearableCodexDescriber::get_always_describe_protect() const
{
  return always_describe_protect;
}
