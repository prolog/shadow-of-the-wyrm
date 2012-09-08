#pragma once
#include "Effect.hpp"

class NullEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(boost::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    virtual bool effect_blessed(boost::shared_ptr<Creature> creature) const;
    virtual bool effect_uncursed(boost::shared_ptr<Creature> creature) const;
    virtual bool effect_cursed(boost::shared_ptr<Creature> creature) const;
};

