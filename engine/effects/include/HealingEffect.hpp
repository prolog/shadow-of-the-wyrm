#pragma once
#include "Effect.hpp"

class HealingEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am);
    
    virtual bool heal(std::shared_ptr<Creature> creature, const double healing_multiplier) const;
    
    virtual int get_random_healing_amount() const;

    static const double BLESSED_MULTIPLIER;
    static const double UNCURSED_MULTIPLIER;
    static const double CURSED_MULTIPLIER;
    static const int BASE_MIN_HP;
    static const int BASE_MAX_HP;
};
