#pragma once
#include "StatusEffect.hpp"

class PoisonStatusEffect : public StatusEffect
{
  public:
    PoisonStatusEffect();

    virtual void tick(boost::shared_ptr<Creature> creature) const;
  
  protected:
    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;

    virtual std::string get_status_identifier() const;
};

