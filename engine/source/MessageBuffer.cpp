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

void MessageBuffer::add_message(const string& new_message, const Colour c)
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
    messages.push_front(make_pair(new_message, c));
  }
  // Otherwise, remove the oldest message, and then add the new one.
  else
  {
    messages.pop_back();
    messages.push_front(make_pair(new_message, c));
  }
}

pair<string, Colour> MessageBuffer::get_message(const size_t pos) const
{
  return messages.at(pos);
}

deque<pair<string, Colour>> MessageBuffer::get_messages(const size_t num_msgs) const
{
  size_t msg_sz = messages.size();
  size_t msgs = std::min<size_t>(msg_sz, num_msgs);

  deque<pair<string, Colour>> msg_buf_copy(messages.begin(), messages.begin() + msgs);
  return msg_buf_copy;
}

void MessageBuffer::clear()
{
  messages.clear();
}

bool MessageBuffer::serialize(ostream& stream) const
{
  Serialize::write_size_t(stream, messages.size());

  for (const auto& m_pair : messages)
  {
    Serialize::write_string(stream, m_pair.first);
    Serialize::write_enum(stream, m_pair.second);
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

    Colour c = Colour::COLOUR_UNDEFINED;
    Serialize::read_enum(stream, c);

    messages.push_back(make_pair(message, c));
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
