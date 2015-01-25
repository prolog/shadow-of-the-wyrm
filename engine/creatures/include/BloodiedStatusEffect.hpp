#pragma once
#include "StatusEffect.hpp"

class BloodiedStatusEffect : public StatusEffect
{
  public:
    BloodiedStatusEffect();
  
  protected:
    virtual Modifier get_base_modifier(CreaturePtr creature) const override;

    virtual std::string get_player_application_message() const override;
    virtual std::string get_player_undo_message() const override;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const override;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_status_identifier() const override;

    static const int BLOODIED_TO_HIT_PENALTY;
};

