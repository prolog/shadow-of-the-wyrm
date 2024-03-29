#pragma once
#include "StatusEffect.hpp"

class MutenessStatusEffect : public StatusEffect
{
  public:
    MutenessStatusEffect();
  
  protected:
    virtual void notify_deities(CreaturePtr initiating, CreaturePtr affected_creature) const override;

    virtual std::string get_player_application_message() const override;
    virtual std::string get_player_undo_message() const override;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const override;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_status_identifier() const override;
};

