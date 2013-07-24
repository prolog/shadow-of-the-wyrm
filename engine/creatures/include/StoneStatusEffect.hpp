#pragma once
#include "StatusEffect.hpp"

class StoneStatusEffect : public StatusEffect
{
  public:
    StoneStatusEffect();
  
  protected:
    // When Stone status runs its course, the creature dies and becomes
    // a statue.
    virtual void finalize(boost::shared_ptr<Creature> creature) const;

    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;

    virtual std::string get_status_identifier() const;
};

