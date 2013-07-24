#pragma once
#include "StatusEffect.hpp"

class StoneStatusEffect : public StatusEffect
{
  public:
    StoneStatusEffect();
  
  protected:
    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;

    virtual std::string get_status_identifier() const;
};

