#pragma once
#include "StatusEffect.hpp"

class ExposedStatusEffect : public StatusEffect
{
  public:
    ExposedStatusEffect();
  
    virtual int get_evade_bonus(std::shared_ptr<Creature> creature) const override;

  protected:
    virtual std::string get_player_application_message() const override;
    virtual std::string get_player_undo_message() const override;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const override;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_status_identifier() const override;

    static const int EXPOSED_EVADE_PENALTY;
};

