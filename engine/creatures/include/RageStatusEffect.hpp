#pragma once
#include "StatusEffect.hpp"

class RageStatusEffect : public StatusEffect
{
  public:
    RageStatusEffect();

    virtual bool is_negative() const override;

  protected:
    virtual void notify_deities(CreaturePtr initiating_creature, CreaturePtr affected_creature) const override;

    virtual std::string get_player_application_message() const override;
    virtual std::string get_player_undo_message() const override;
    virtual std::string get_player_finalize_message() const override;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const override;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_status_identifier() const override;
};

