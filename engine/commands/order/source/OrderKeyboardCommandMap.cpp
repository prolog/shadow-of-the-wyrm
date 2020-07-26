#include "CursesConstants.hpp"
#include "OrderCommandKeys.hpp"
#include "OrderKeyboardCommandMap.hpp"

using namespace std;

OrderKeyboardCommandMap::OrderKeyboardCommandMap()
{
}

OrderKeyboardCommandMap::~OrderKeyboardCommandMap()
{
}

void OrderKeyboardCommandMap::command_not_found(const string& keyboard_input)
{
  if (!keyboard_input.empty())
  {
    // Fail silently.
  }
}

// Settings currently does nothing here.
void OrderKeyboardCommandMap::initialize_command_mapping(const Settings& settings)
{
  string esc_key;
  esc_key = NC_ESCAPE_KEY;

  command_mapping.clear();
  command_mapping = KeyboardCommandMappingMap{ { std::to_string('a'), OrderCommandKeys::ATTACK },
  { std::to_string('b'), OrderCommandKeys::FOLLOW },
  { std::to_string('c'), OrderCommandKeys::FREEZE },
  { std::to_string('z'), OrderCommandKeys::EXIT_ORDER },
  { std::to_string('Z'), OrderCommandKeys::EXIT_ORDER },
  { std::to_string(NC_ESCAPE_KEY), OrderCommandKeys::EXIT_ORDER },
  { esc_key, OrderCommandKeys::EXIT_ORDER } };
}

KeyboardCommandMap* OrderKeyboardCommandMap::clone()
{
  return new OrderKeyboardCommandMap(*this);
}

string OrderKeyboardCommandMap::get_settings_prefix() const
{
  return "key_order_";
}

ClassIdentifier OrderKeyboardCommandMap::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_ORDER_KEYBOARD_COMMAND_MAP;
}

#ifdef UNIT_TESTS
#include "unit_tests/OrderKeyboardCommandMap_test.cpp"
#endif
  