#include <boost/range/adaptors.hpp>
#include <boost/range/algorithm.hpp>
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "MessageManager.hpp"
#include "StatusEffectFactory.hpp"
#include "TimewalkEffect.hpp"

using namespace std;

TimewalkEffect::TimewalkEffect()
{
}

string TimewalkEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature)
  {
    effect_msg = EffectTextKeys::get_timewalk_effect_message(creature->get_description_sid(), creature->get_is_player());
  }

  return effect_msg;
}

Effect* TimewalkEffect::clone()
{
  return new TimewalkEffect(*this);
}

bool TimewalkEffect::effect_blessed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  return timewalk(creature);
}

bool TimewalkEffect::effect_uncursed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  return timewalk(creature);
}

bool TimewalkEffect::effect_cursed(CreaturePtr creature, ActionManager * /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  return timewalk(creature);
}

bool TimewalkEffect::timewalk(CreaturePtr creature)
{
  bool timewalked = false;

  if (creature != nullptr)
  {
    StatusEffectPtr tw = StatusEffectFactory::create_status_effect(this->get_originator(), StatusIdentifiers::STATUS_ID_TIMEWALK, creature->get_id());
    tw->apply_change(creature, creature->get_level().get_current());
    Game::instance().get_sound()->play(SoundEffectID::TIMEWALK);

    timewalked = true;
  }

  return timewalked;
}

