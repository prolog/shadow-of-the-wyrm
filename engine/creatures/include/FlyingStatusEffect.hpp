#pragma once
#include "FloatingStatusEffect.hpp"

class FlyingStatusEffect : public FloatingStatusEffect
{
  public:
    FlyingStatusEffect();

    virtual bool is_negative() const override;
    virtual std::string get_sound_effect() const override;

  protected:
    virtual std::string get_player_application_message() const override;
    virtual std::string get_player_undo_message() const override;
    virtual std::string get_player_finalize_message() const override;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const override;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_status_identifier() const override;
};

