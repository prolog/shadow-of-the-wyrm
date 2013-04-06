#include "AdditionalEffectMessages.hpp"
#include "EffectTextKeys.hpp"

SweetTasteEffectMessage::SweetTasteEffectMessage() :
AdditionalEffectMessage(EffectTextKeys::EFFECT_SWEET_TASTE)
{
}

AdditionalEffectMessage* SweetTasteEffectMessage::clone()
{
  return new SweetTasteEffectMessage(*this);
}

