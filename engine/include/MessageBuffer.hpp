#pragma once
#include "ISerializable.hpp"

// Stores message history up to a particular number of messages, rather
// than up to a particular max size.
class MessageBuffer : public ISerializable
{
  public:
    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;
    bool operator==(const MessageBuffer& mb) const;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
