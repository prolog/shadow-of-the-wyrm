#include "EntranceState.hpp"

EntranceState::EntranceState()
: state(ENTRANCE_TYPE_OPEN)
{
}

EntranceState::EntranceState(const EntranceStateType new_state)
: state(new_state)
{
}

void EntranceState::set_state(const EntranceStateType new_state)
{
  state = new_state;
}

EntranceStateType EntranceState::get_state() const
{
  return state;
}

uchar EntranceState::get_symbol() const
{
  uchar symbol;
  
  switch(state)
  {
    case ENTRANCE_TYPE_DESTROYED:
      symbol = '.';
      break;
    case ENTRANCE_TYPE_OPEN:
      symbol = '`';
      break;
    case ENTRANCE_TYPE_CLOSED:
    default:
      symbol = '+';
      break;
  }
  
  return symbol;
}
