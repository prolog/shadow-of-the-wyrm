#include "Messages.hpp"

void Messages::add(const Message& message)
{
	messages.push_back(message);
}

std::vector<Message> Messages::get_messages() const
{
	return messages;
}

void Messages::clear()
{
	messages.clear();
}

#ifdef UNIT_TESTS
#include "unit_tests/Messages_test.cpp"
#endif
