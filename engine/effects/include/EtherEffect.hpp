#pragma once
#include "HealingEffect.hpp"

// Basically, a type of healing effect, but instead of healing HP, heals
// AP.
class EtherEffect : public HealingEffect
{
  public:
    EtherEffect();
    
    virtual std::string get_effect_identification_message(boost::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    virtual bool heal(boost::shared_ptr<Creature> creature, const float healing_multiplier) const;

  private:
    ClassIdentifier internal_class_identifier() const;
};
