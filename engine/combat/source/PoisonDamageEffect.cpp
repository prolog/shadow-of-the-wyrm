#include "Game.hpp"
#include "PoisonDamageEffect.hpp"
#include "Random.hpp"
#include "RNG.hpp"
#include "StatusAilmentTextKeys.hpp"
#include "StatusDuration.hpp"
#include "StatusTypes.hpp"
#include "StringTable.hpp"

using namespace std;

const int PoisonDamageEffect::BASE_PCT_CHANCE_POISON = 25;

const int PoisonDamageEffect::POISON_DURATION_MEAN = 30;

void PoisonDamageEffect::apply(CreaturePtr creature, const int damage_dealt) const
{
  if (RNG::percent_chance(BASE_PCT_CHANCE_POISON) && creature && !creature->has_status(StatusIdentifiers::STATUS_ID_POISON))
  {
    Game& game = Game::instance();
    double current_seconds_since_game_start = game.get_current_world()->get_calendar().get_seconds();

    // Poison duration is described by a Poisson distribution, with the
    // average poisoning lasting about half an hour.
    PoissonDistribution p(POISON_DURATION_MEAN);
    int duration = p.next();
    StatusDuration poison_duration(current_seconds_since_game_start + (duration * 60.0));

    creature->set_status(StatusIdentifiers::STATUS_ID_POISON, true);
    creature->set_status_duration(StatusIdentifiers::STATUS_ID_POISON, poison_duration);
  }
}

string PoisonDamageEffect::get_player_application_message() const
{
  string message = StringTable::get(StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISONED);
  return message;
}

