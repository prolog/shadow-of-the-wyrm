#pragma once
#include "Effect.hpp"

// Used for determining what to do to a creature's equipment/inventory when
// the effect is invoked.
enum struct UncursingEffectType
{
  UNCURSING_EFFECT_NO_EFFECT,
  UNCURSING_EFFECT_UNCURSE,
  UNCURSING_EFFECT_CURSE
};

class UncursingEffect : public Effect
{
  public:
    UncursingEffect();
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual bool uncurse(std::shared_ptr<Creature> creature, const UncursingEffectType uet_eq, const UncursingEffectType uet_inv);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
};

