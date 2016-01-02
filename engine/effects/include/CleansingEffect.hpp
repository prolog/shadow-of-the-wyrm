#pragma once
#include "Effect.hpp"

class CleansingEffect : public Effect
{
  public:
    CleansingEffect();
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual bool cleansing(std::shared_ptr<Creature> creature, const float map_creature_regen_multiplier);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
};

