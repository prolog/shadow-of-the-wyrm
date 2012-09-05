#pragma once
#include "Effect.hpp"

class HealingEffect : public Effect
{
  public:
    virtual Effect* clone();

  protected:
    virtual bool effect_blessed(boost::shared_ptr<Creature> creature) const;
    virtual bool effect_uncursed(boost::shared_ptr<Creature> creature) const;
    virtual bool effect_cursed(boost::shared_ptr<Creature> creature) const;
};
