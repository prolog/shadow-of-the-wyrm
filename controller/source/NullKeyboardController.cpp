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
