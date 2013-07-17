#pragma once
#include "StatusEffect.hpp"

class ParalysisStatusEffect : public StatusEffect
{
  public:
    ParalysisStatusEffect();
  
  protected:
    virtual std::string get_player_application_message() const;
    virtual std::string get_player_undo_message() const;

    virtual std::string get_status_identifier() const;
};

