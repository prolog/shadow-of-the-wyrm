#include "AdditionalEffectMessage.hpp"

class SweetTasteEffectMessage : public AdditionalEffectMessage
{
  public:
    SweetTasteEffectMessage();

    AdditionalEffectMessage* clone();

  private:
    ClassIdentifier internal_class_identifier() const;
};

