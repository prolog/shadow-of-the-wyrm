#pragma once
#include "StatusEffect.hpp"

class BlindedStatusEffect : public StatusEffect
{
  public:
    BlindedStatusEffect();
  
    virtual int get_to_hit_bonus(boost::shared_ptr<Creature> creature) const;
    virtual int get_evade_bonus(boost::shared_ptr<Creature> creature) const;

  protected:
    virtual bool after_apply(boost::shared_ptr<Creature> creature) const;
    virtual void after_undo(boost::shared_ptr<Creature> creature) const;

    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;
    virtual std::string get_npc_application_message(boost::shared_ptr<Creature> creature) const;
    virtual std::string get_npc_undo_message(boost::shared_ptr<Creature> creature) const;

    virtual std::string get_status_identifier() const;

    static const int BLINDED_TO_HIT_PENALTY;
    static const int BLINDED_EVADE_PENALTY;
};

