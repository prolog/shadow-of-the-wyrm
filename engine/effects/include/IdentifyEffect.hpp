#pragma once
#include "Effect.hpp"

class IdentifyEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am);
    
    // The actual identification message
    std::string identification_msg;
};

