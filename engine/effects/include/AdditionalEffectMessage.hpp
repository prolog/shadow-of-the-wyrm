#pragma once
#include <string>
#include <boost/shared_ptr.hpp>
#include "ISerializable.hpp"

// This class defines an abstract base class for messages that should be 
// displayed to the target of a particular effect.  E.g., drinking a potion
// of ether will display, "This tastes sweet," (an IEffectMessage) in 
// addition to potentially displaying, "You feel more powerful" (the
// actual identification message).

class AdditionalEffectMessage : public ISerializable
{
  public:
    virtual void add_effect_message() const;

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

    virtual AdditionalEffectMessage* clone() = 0;

  protected:
    AdditionalEffectMessage(const std::string& effect_msg_sid);

    std::string effect_message_sid;

  private:
    ClassIdentifier internal_class_identifier() const = 0;
};

typedef boost::shared_ptr<AdditionalEffectMessage> AdditionalEffectMessagePtr;

