#pragma once
#include "Effect.hpp"

class RemoveStatusEffect : public Effect
{
  public:
    RemoveStatusEffect(const std::string& status_identifier);
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const override;
    virtual Effect* clone() override;

  protected:
    virtual bool remove_status(std::shared_ptr<Creature> creature);
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am) override;

    std::string status_id;
};

