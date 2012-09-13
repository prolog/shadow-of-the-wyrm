#pragma once
#include "Effect.hpp"

class IdentifyEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(boost::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    virtual bool effect_blessed(boost::shared_ptr<Creature> creature);
    virtual bool effect_uncursed(boost::shared_ptr<Creature> creature);
    virtual bool effect_cursed(boost::shared_ptr<Creature> creature);
    
    // The actual identification message
    std::string identification_msg;
};

