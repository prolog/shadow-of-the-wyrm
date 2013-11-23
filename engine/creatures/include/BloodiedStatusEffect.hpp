#pragma once
#include "StatusEffect.hpp"

class BloodiedStatusEffect : public StatusEffect
{
  public:
    BloodiedStatusEffect();
  
    virtual int get_to_hit_bonus(std::shared_ptr<Creature> creature) const;

  protected:
    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;
    virtual std::string get_npc_application_message(std::shared_ptr<Creature> creature) const;
    virtual std::string get_npc_undo_message(std::shared_ptr<Creature> creature) const;

    virtual std::string get_status_identifier() const;

    static const int BLOODIED_TO_HIT_PENALTY;
};

