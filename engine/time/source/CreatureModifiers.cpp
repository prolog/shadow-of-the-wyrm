#include "ActionTextKeys.hpp"
#include "CreatureModifiers.hpp"
#include "CreatureUtils.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "MessageManagerFactory.hpp"
#include "SpellAdditionalProperties.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

void CreatureModifiers::tick(CreaturePtr creature, TilePtr tile, const ulonglong minutes_this_tick, const ulonglong total_minutes_elapsed)
{
  if (creature)
  {
    Game& game = Game::instance();
    double current_seconds = GameUtils::get_seconds(game);

    CreatureUtils::mark_modifiers_for_deletion(creature, current_seconds);
    CreatureUtils::remove_modifiers(creature);
  }
}
