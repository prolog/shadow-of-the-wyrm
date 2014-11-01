#pragma once
#include "Effect.hpp"
#include "GainAttributesTypes.hpp"

class GainAttributesEffect : public Effect
{
  public:
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    
    virtual bool gain_attributes(std::shared_ptr<Creature> creature, const std::vector<GainAttributesEnum>& attr_to_gain) const;
};
