#pragma once
#include "Effect.hpp"

// Used for determining what to do to a creature's equipment/inventory when
// the effect is invoked.
enum struct BlessEffectType
{
  BLESS_EFFECT_UNCURSE_ITEM,
  BLESS_EFFECT_BLESS_ITEM,
  BLESS_EFFECT_BLESS_ITEMS_OF_TYPE
};

class BlessEffect : public Effect
{
  public:
    BlessEffect();
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual bool bless(std::shared_ptr<Creature> creature, const BlessEffectType bet, ActionManager * const am);

    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
};

