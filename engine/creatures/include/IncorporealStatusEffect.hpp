#pragma once
#include "FloatingStatusEffect.hpp"

class IncorporealStatusEffect : public FloatingStatusEffect
{
  public:
    IncorporealStatusEffect();

    bool is_negative() const override;

  protected:
    virtual void after_undo(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_player_application_message() const override;
    virtual std::string get_player_undo_message() const override;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const override;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_status_identifier() const override;
};

