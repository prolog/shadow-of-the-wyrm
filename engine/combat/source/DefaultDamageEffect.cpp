#include "DefaultDamageEffect.hpp"

using namespace std;

void DefaultDamageEffect::apply(CreaturePtr creature, const int damage_dealt) const
{
}

string DefaultDamageEffect::get_player_application_message() const
{
  string no_message;
  return no_message;
}
