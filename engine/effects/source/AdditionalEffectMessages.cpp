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

ClassIdentifier SweetTasteEffectMessage::internal_class_identifier() const
{
  return CLASS_ID_SWEET_TASTE_EFFECT_MESSAGE;
}