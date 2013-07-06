#include "PoisonDamageEffect.hpp"
#include "RNG.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusTypes.hpp"
#include "StringTable.hpp"

using namespace std;

const int PoisonDamageEffect::BASE_PCT_CHANCE_POISON = 25;

// 10 minutes is the minimum to work the poison out of one's system.
const int PoisonDamageEffect::BASE_POISON_DURATION = 10;
const int PoisonDamageEffect::MAX_POISON_DURATION = 60;

void PoisonDamageEffect::apply(CreaturePtr creature, const int damage_dealt) const
{
  if (RNG::percent_chance(BASE_PCT_CHANCE_POISON) && creature)
  {
    creature->set_status(StatusIdentifiers::STATUS_ID_POISON, true);
  }
}

string PoisonDamageEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISONED);
  return message;
}

