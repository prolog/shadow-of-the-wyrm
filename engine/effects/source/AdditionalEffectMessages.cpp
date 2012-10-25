#include "StringConstants.hpp"
#include "AdditionalEffectMessages.hpp"

SweetTasteEffectMessage::SweetTasteEffectMessage() :
AdditionalEffectMessage(EffectTextKeys::EFFECT_SWEET_TASTE)
{
}

AdditionalEffectMessage* SweetTasteEffectMessage::clone()
{
  return new SweetTasteEffectMessage(*this);
}

