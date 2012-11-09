#include "EntranceState.hpp"
#include "Serialize.hpp"

using namespace std;

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

bool EntranceState::serialize(ostream& stream)
{
  Serialize::write_enum(stream, state);
  
  return true;
}

bool EntranceState::deserialize(istream& stream)
{
  Serialize::read_enum(stream, state);

  return true;
}

ClassIdentifier EntranceState::internal_class_identifier() const
{
  return CLASS_ID_ENTRANCE_STATE;
}

#ifdef UNIT_TESTS
#include "unit_tests/EntranceState_test.cpp"
#endif

