#pragma once
#include "Effect.hpp"

class FruitJuiceEffect : public Effect
{
  public:
    FruitJuiceEffect();
    
    virtual std::string get_effect_identification_message(boost::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    virtual bool effect_blessed(boost::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_uncursed(boost::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_cursed(boost::shared_ptr<Creature> creature, ActionManager * const am);

  private:
    ClassIdentifier internal_class_identifier() const;
};

