#include "Controller.hpp"

using namespace std;

Controller::~Controller()
{
}

// Just check the class identifier.
bool Controller::operator==(const Controller& c) const
{
  return (internal_class_identifier() == c.internal_class_identifier());
}

// SDL needs to peek at events periodically or else the window freezes,
// Not Responding, blah blah blah. Curses is great because curses doesn't gaf.
void Controller::poll_event()
{
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
bool Controller::serialize(ostream&) const
{
  return true;
}

bool Controller::deserialize(istream&)
{
  return true;
}

