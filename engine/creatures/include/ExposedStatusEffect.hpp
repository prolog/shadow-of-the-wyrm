#pragma once
#include "StatusEffect.hpp"

class ExposedStatusEffect : public StatusEffect
{
  public:
    ExposedStatusEffect();
  
    virtual int get_evade_bonus(std::shared_ptr<Creature> creature) const;

  protected:
    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const;

    virtual std::string get_status_identifier() const;

    static const int EXPOSED_EVADE_PENALTY;
};

