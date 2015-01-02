#include "MessageBuffer.hpp"
#include "Serialize.hpp"

using namespace std;

const size_t MessageBuffer::DEFAULT_MAX_BUFFER_SIZE = 1000;

MessageBuffer::MessageBuffer()
: max_messages(DEFAULT_MAX_BUFFER_SIZE)
{
}

MessageBuffer::MessageBuffer(const size_t new_size_max)
: max_messages(new_size_max)
{
}

bool MessageBuffer::operator==(const MessageBuffer& mb) const
{
  bool result = true;

  result = result && (max_messages == mb.max_messages);
  result = result && (messages == mb.messages);

  return result;
}

size_t MessageBuffer::size() const
{
  return messages.size();
}

size_t MessageBuffer::capacity() const
{
  return max_messages;
}

void MessageBuffer::add_message(const string& new_message)
{
  // If the message buffer is at less than full capacity,
  // add to the front.
  //
  // Having it at the front makes displaying the message
  // history easier, since the first page of the menu
  // will be the newest info - the player shouldn't have
  // to page as much.
  if (messages.size() < max_messages)
  {
    messages.push_front(new_message);
  }
  // Otherwise, remove the oldest message, and then add the new one.
  else
  {
    messages.pop_back();
    messages.push_front(new_message);
  }
}

string MessageBuffer::get_message(const size_t pos) const
{
  return messages.at(pos);
}

void MessageBuffer::clear()
{
  messages.clear();
}

bool MessageBuffer::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, messages.size());

  for (const string& message : messages)
  {
    Serialize::write_string(stream, message);
  }

  return true;
}

bool MessageBuffer::deserialize(istream& stream)
{
  size_t size = 0;
  Serialize::read_size_t(stream, size);

  for (size_t i = 0; i < size; i++)
  {
    string message;
    Serialize::read_string(stream, message);

    messages.push_back(message);
  }

  return true;
}

ClassIdentifier MessageBuffer::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_MESSAGE_BUFFER;
}

#ifdef UNIT_TESTS
#include "unit_tests/MessageBuffer_test.cpp"
#endif
