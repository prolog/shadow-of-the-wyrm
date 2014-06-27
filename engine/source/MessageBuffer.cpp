#include "MessageBuffer.hpp"

using namespace std;

bool MessageBuffer::operator==(const MessageBuffer& mb) const
{
  bool result = true;

  // ...

  return result;
}

bool MessageBuffer::serialize(ostream& stream) const
{
  return true;
}

bool MessageBuffer::deserialize(istream& stream)
{
  return true;
}

ClassIdentifier MessageBuffer::internal_class_identifier() const
{
  return CLASS_ID_MESSAGE_BUFFER;
}

#ifdef UNIT_TESTS
#include "unit_tests/MessageBuffer_test.cpp"
#endif
