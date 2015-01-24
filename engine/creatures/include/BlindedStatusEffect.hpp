#pragma once
#include "StatusEffect.hpp"

class BlindedStatusEffect : public StatusEffect
{
  public:
    BlindedStatusEffect();
  
    virtual int get_to_hit_bonus(std::shared_ptr<Creature> creature) const override;

  protected:
    virtual Modifier get_base_modifier() const override;

    virtual bool after_apply(std::shared_ptr<Creature> creature) const override;
    virtual void after_undo(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_player_application_message() const override;
    virtual std::string get_player_undo_message() const override;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const override;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const override;

    virtual std::string get_status_identifier() const override;

    static const int BLINDED_TO_HIT_PENALTY;
    static const int BLINDED_EVADE_PENALTY;
};

