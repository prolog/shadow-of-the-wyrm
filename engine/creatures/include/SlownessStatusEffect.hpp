#pragma once
#include "StatusEffect.hpp"

class SlownessStatusEffect : public StatusEffect
{
  public:
    SlownessStatusEffect();
  
  protected:
    virtual void after_apply(boost::shared_ptr<Creature> creature) const;
    virtual void after_undo(boost::shared_ptr<Creature> creature) const;

    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;

    virtual std::string get_status_identifier() const;
};

