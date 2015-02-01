#pragma once
#include "Effect.hpp"

class HealingEffect : public Effect
{
  public:
    HealingEffect();

    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

    virtual void read_properties(const std::map<std::string, std::string>& properties) override;

  protected:
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    
    virtual bool heal(std::shared_ptr<Creature> creature, const double healing_multiplier) const;
    
    virtual int get_random_healing_amount() const;

    // The instance variables will either be equal to the static amounts
    // (by default), or to values read from the properties.
    int min_hp;
    int max_hp;

    static const double BLESSED_MULTIPLIER;
    static const double UNCURSED_MULTIPLIER;
    static const double CURSED_MULTIPLIER;
    static const int BASE_MIN_HP;
    static const int BASE_MAX_HP;
    static const std::string HEALING_MIN;
    static const std::string HEALING_MAX;
};
