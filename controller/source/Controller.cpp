#include "Controller.hpp"

using namespace std;

// Just check the class identifier.
bool Controller::operator==(const Controller& c) const
{
  return (internal_class_identifier() == c.internal_class_identifier());
}

int Controller::get_char_as_int()
{
  return translate_kb_input(read_char_as_int());
}

pair<bool, int> Controller::get_char_as_int_nb()
{
  pair<bool, int> input = read_char_as_int_nb();

  if (input.first)
  {
    input.second = translate_kb_input(input.second);
  }

  return input;
}

// Controllers are stateless.
bool Controller::serialize(ostream& stream) const
{
  return true;
}

bool Controller::deserialize(istream& stream)
{
  return true;
}

