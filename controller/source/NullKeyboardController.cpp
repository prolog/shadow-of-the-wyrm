#include "NullKeyboardController.hpp"

std::string NullKeyboardController::get_line()
{
  std::string empty;
  return empty;
}

int NullKeyboardController::get_char_as_int()
{
  return -1;
}

std::pair<bool, int> NullKeyboardController::get_char_as_int_nb()
{
  return std::make_pair(false, -1);
}

Controller* NullKeyboardController::clone()
{
  return new NullKeyboardController(*this);
}

ClassIdentifier NullKeyboardController::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_NULL_KEYBOARD_CONTROLLER;
}
