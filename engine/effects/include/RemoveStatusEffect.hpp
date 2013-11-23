#pragma once
#include "Effect.hpp"

class RemoveStatusEffect : public Effect
{
  public:
    RemoveStatusEffect(const std::string& status_identifier);
    
    virtual std::string get_effect_identification_message(std::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    virtual bool remove_status(std::shared_ptr<Creature> creature);
    virtual bool effect_blessed(std::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_uncursed(std::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_cursed(std::shared_ptr<Creature> creature, ActionManager * const am);

    std::string status_id;
};

