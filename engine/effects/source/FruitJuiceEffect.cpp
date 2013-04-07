#include <boost/make_shared.hpp>
#include "AdditionalEffectMessages.hpp"
#include "Creature.hpp"
#include "EffectTextKeys.hpp"
#include "MessageManager.hpp"
#include "FruitJuiceEffect.hpp"

using std::string;

// Add an additional message about sweet taste
FruitJuiceEffect::FruitJuiceEffect()
{
  AdditionalEffectMessagePtr sweet_taste = boost::make_shared<SweetTasteEffectMessage>();
  additional_effect_messages.push_back(sweet_taste);
}

string FruitJuiceEffect::get_effect_identification_message(CreaturePtr creature) const
{
  string effect_msg;

  if (creature)
  {
    // Only return info about the sweet taste if the creature is the player
    if (creature->get_is_player())
    {
      effect_msg = StringTable::get(EffectTextKeys::EFFECT_FRUIT_JUICE);
    }
  }

  return effect_msg;
}

Effect* FruitJuiceEffect::clone()
{
  return new FruitJuiceEffect(*this);
}

// When the effect is blessed, the player can figure out what it is
// (potion of fruit juice, etc).
bool FruitJuiceEffect::effect_blessed(CreaturePtr creature, ActionManager * const am)
{
  return true;
}

// When the effect is uncursed, the player at least gets a clue in the form
// of "You suddenly taste something very sweet."
bool FruitJuiceEffect::effect_uncursed(CreaturePtr creature, ActionManager * const am)
{
  return false;
}

bool FruitJuiceEffect::effect_cursed(CreaturePtr creature, ActionManager * am)
{
  return false;
}

