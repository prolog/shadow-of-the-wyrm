#pragma once
#include "Effect.hpp"

class RemoveStatusEffect : public Effect
{
  public:
    RemoveStatusEffect(const std::string& status_identifier);
    
    virtual std::string get_effect_identification_message(boost::shared_ptr<Creature> creature) const;
    virtual Effect* clone();

  protected:
    virtual bool remove_status(boost::shared_ptr<Creature> creature);
    virtual bool effect_blessed(boost::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_uncursed(boost::shared_ptr<Creature> creature, ActionManager * const am);
    virtual bool effect_cursed(boost::shared_ptr<Creature> creature, ActionManager * const am);

    std::string status_id;
};

