#include "Message.hpp"

Message::Message
(
  const std::string& new_content
, const Colour new_colour
, const MessageImportance& new_importance
)
: content(new_content)
, colour(new_colour)
, importance(new_importance)
{
}

void Message::set_content(const std::string& new_content)
{
	content = new_content;
}

std::string Message::get_content() const
{
	return content;
}

void Message::set_colour(const Colour new_colour)
{
  colour = new_colour;
}

Colour Message::get_colour() const
{
  return colour;
}

void Message::set_importance(const MessageImportance& new_importance)
{
	importance = new_importance;
}

MessageImportance Message::get_importance() const
{
	return importance;
}

void Message::set_id(const boost::uuids::uuid& new_id)
{
	id = new_id;
}

boost::uuids::uuid Message::get_id() const
{
	return id;
}

#ifdef UNIT_TESTS
#include "unit_tests/Message_test.cpp"
#endif
