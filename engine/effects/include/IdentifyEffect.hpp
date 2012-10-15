#pragma once
#include "Effect.hpp"

class IdentifyEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(boost::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

    virtual bool serialize(std::ostream& stream);
    virtual bool deserialize(std::istream& stream);

  protected:
    virtual bool effect_blessed(boost::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_uncursed(boost::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_cursed(boost::shared_ptr<Creature> creature, ActionManager * const am);
    
    // The actual identification message
    std::string identification_msg;

  private:
    ClassIdentifier internal_class_identifier() const;
};

