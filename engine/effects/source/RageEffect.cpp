#include "RageEffect.hpp"
#include "ActionTextKeys.hpp"
#include "EffectTextKeys.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

// Will be handled by applying the rage status effect.
string RageEffect::get_effect_identification_message(std::shared_ptr<Creature> /*creature*/) const
{
  string no_effect;

  return no_effect;
}

Effect* RageEffect::clone()
{
  return new RageEffect(*this);
}

string RageEffect::get_status_id() const
{
  return StatusIdentifiers::STATUS_ID_RAGE;
}

bool RageEffect::rage(CreaturePtr creature)
{
  bool effect_applied = false;
  string rage_s = StatusIdentifiers::STATUS_ID_RAGE;

  if (creature != nullptr && !creature->has_status(rage_s))
  {
    StatusEffectPtr rage = StatusEffectFactory::create_status_effect(this->get_originator(), rage_s, source_id);

    if (rage != nullptr)
    {
      rage->apply_change(creature, creature->get_level().get_current());
      effect_applied = true;
    }

    if (effect_applied)
    {
      Game::instance().get_sound()->play(SoundEffectID::RAGE);
    }
  }

  return effect_applied;
}

bool RageEffect::effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  return rage(creature);
}

bool RageEffect::effect_uncursed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  return rage(creature);
}

// When cursed, the rage effect doesn't take hold properly - add a message
// about being angry, but that's it.
bool RageEffect::effect_cursed(CreaturePtr creature, ActionManager * const /*am*/, const Coordinate& /*affected_coordinate*/, TilePtr /*affected_tile*/)
{
  IMessageManager& manager = MMF::instance(MessageTransmit::FOV, creature, creature && creature->get_is_player());
  manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ANGRY));
  manager.send();

  return true;
}
