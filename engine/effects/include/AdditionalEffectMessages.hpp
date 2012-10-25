#include "AdditionalEffectMessage.hpp"

class SweetTasteEffectMessage : public AdditionalEffectMessage
{
  public:
    SweetTasteEffectMessage();

    AdditionalEffectMessage* clone();
};

