#pragma once
#include "PoisonCalculator.hpp"
#include "StatusEffect.hpp"

class PoisonStatusEffect : public StatusEffect
{
  public:
    virtual bool should_apply_change(boost::shared_ptr<Creature> creature) const;
    virtual void tick(boost::shared_ptr<Creature> creature) const;
  
  protected:
    virtual void apply(boost::shared_ptr<Creature> creature) const;
    virtual void finalize(boost::shared_ptr<Creature> creature) const;
    virtual void undo(boost::shared_ptr<Creature> creature) const;

    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;

    PoisonCalculator poison_calc;
};

