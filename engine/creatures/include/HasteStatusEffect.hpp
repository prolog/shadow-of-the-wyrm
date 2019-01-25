#pragma once
#include "StatusEffect.hpp"

class HasteStatusEffect : public StatusEffect
{
  public:
    HasteStatusEffect();

    virtual bool is_negative() const override;
  
  protected:
    virtual Modifier get_base_modifier(std::shared_ptr<Creature> creature, const int danger_level) const override;
    virtual bool after_apply(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_player_application_message() const override;
    virtual std::string get_player_undo_message() const override;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const override;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_status_identifier() const override;
};

