#pragma once
#include "StatusEffect.hpp"

class WaterBreathingStatusEffect : public StatusEffect
{
  public:
    WaterBreathingStatusEffect();

    virtual bool is_negative() const override;

  protected:
    virtual std::string get_player_application_message() const override;
    virtual std::string get_player_undo_message() const override;
    virtual std::string get_player_finalize_message() const override;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const override;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const override;
    virtual void after_finalize(std::shared_ptr<Creature> creature) const;

    virtual std::string get_status_identifier() const override;
};

