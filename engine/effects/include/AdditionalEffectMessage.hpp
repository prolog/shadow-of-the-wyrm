#pragma once
#include <string>
#include <memory>
#include "Creature.hpp"

// This class defines an abstract base class for messages that should be 
// displayed to the target of a particular effect.  E.g., drinking a potion
// of ether will display, "This tastes sweet," (an IEffectMessage) in 
// addition to potentially displaying, "You feel more powerful" (the
// actual identification message).

class AdditionalEffectMessage
{
  public:
    virtual void add_effect_message(CreaturePtr creature) const;

    virtual AdditionalEffectMessage* clone() = 0;

  protected:
    AdditionalEffectMessage(const std::string& effect_msg_sid);

    std::string effect_message_sid;
};

using AdditionalEffectMessagePtr = std::shared_ptr<AdditionalEffectMessage>;

