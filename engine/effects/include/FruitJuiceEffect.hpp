#pragma once
#include "Effect.hpp"

class FruitJuiceEffect : public Effect
{
  public:
    FruitJuiceEffect();
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am);
};

