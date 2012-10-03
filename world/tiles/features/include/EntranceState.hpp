#pragma once
#include "common.hpp"
#include "EntranceTypes.hpp"

class EntranceState
{
  public:
    EntranceState();
    EntranceState(const EntranceStateType new_state);
    
    void set_state(const EntranceStateType new_state);
    EntranceStateType get_state() const;
    
    uchar get_symbol() const;
    
  protected:
    EntranceStateType state;
};
