#include "NullKeyboardController.hpp"

std::pair<int, std::set<KeyModifierType>> NullKeyboardController::read_char_as_int()
{
  return make_pair(-1, std::set<KeyModifierType>());
}

std::pair<bool, int> NullKeyboardController::read_char_as_int_nb()
{
  return std::make_pair(false, -1);
}

int NullKeyboardController::translate_kb_input(const int input, const std::set<KeyModifierType>& /* type */)
{
  return input;
}

Controller* NullKeyboardController::clone()
{
  return new NullKeyboardController(*this);
}

ClassIdentifier NullKeyboardController::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER;
}
