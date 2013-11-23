#pragma once
#include "StatusEffect.hpp"

class IncorporealStatusEffect : public StatusEffect
{
  public:
    IncorporealStatusEffect();

  protected:
    virtual void after_undo(std::shared_ptr<Creature> creature) const;

    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const;

    virtual std::string get_status_identifier() const;
};

