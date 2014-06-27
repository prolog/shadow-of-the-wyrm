#pragma once
#include <deque>
#include "ISerializable.hpp"

// Stores message history up to a particular number of messages, rather
// than up to a particular max size.
class MessageBuffer : public ISerializable
{
  public:
    MessageBuffer();
    MessageBuffer(const size_t max_size);

    size_t size() const;
    size_t capacity() const;

    void add_message(const std::string& new_message);
    std::string get_message(const size_t pos) const;
    void clear();

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
    bool operator==(const MessageBuffer& mb) const;

  protected:
    std::deque<std::string> messages;
    size_t max_messages;
    static const size_t DEFAULT_MAX_BUFFER_SIZE;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
