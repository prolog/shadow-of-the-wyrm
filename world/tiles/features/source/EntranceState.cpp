#include "EntranceState.hpp"
#include "Serialize.hpp"

using namespace std;

EntranceState::EntranceState()
: state(EntranceStateType::ENTRANCE_TYPE_OPEN)
{
}

EntranceState::EntranceState(const EntranceStateType new_state)
: state(new_state)
{
}

bool EntranceState::operator==(const EntranceState& st) const
{
  bool result = true;

  result = result && (state == st.state);

  return result;
}

void EntranceState::set_state(const EntranceStateType new_state)
{
  state = new_state;
}

EntranceStateType EntranceState::get_state() const
{
  return state;
}

Symbol EntranceState::get_symbol() const
{
  pair<uchar, string> symbol_and_ref = {'.', SpritesheetReference::SPRITESHEET_ENTRANCE_DESTROYED};
  Colour c = Colour::COLOUR_WHITE;

  switch(state)
  {
    case EntranceStateType::ENTRANCE_TYPE_DESTROYED:
      symbol_and_ref = {'.', SpritesheetReference::SPRITESHEET_ENTRANCE_DESTROYED};
      break;
    case EntranceStateType::ENTRANCE_TYPE_OPEN:
      symbol_and_ref = {'`', SpritesheetReference::SPRITESHEET_ENTRANCE_OPEN};
      break;
    case EntranceStateType::ENTRANCE_TYPE_CLOSED:
    default:
      symbol_and_ref = {'+', SpritesheetReference::SPRITESHEET_ENTRANCE_CLOSED};
      break;
  }
  
  Symbol s(symbol_and_ref.first, c, SpritesheetLocation(SpritesheetIndex::SPRITESHEET_INDEX_SYSTEM, symbol_and_ref.second));
  return s;
}

bool EntranceState::serialize(ostream& stream) const
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
  return ClassIdentifier::CLASS_ID_ENTRANCE_STATE;
}

#ifdef UNIT_TESTS
#include "unit_tests/EntranceState_test.cpp"
#endif

