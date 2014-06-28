#include <sstream>
#include "Conversion.hpp"
#include "Game.hpp"
#include "MessageBufferDumper.hpp"
#include "TextKeys.hpp"
#include "StringTable.hpp"

using namespace std;

const size_t MessageBufferDumper::DEFAULT_NUM_MSGS = 15;

MessageBufferDumper::MessageBufferDumper(const IMessageManager& new_mm, const uint new_max_cols)
: mm(new_mm), num_msgs(DEFAULT_NUM_MSGS), num_cols(new_max_cols)
{
}

string MessageBufferDumper::str() const
{
  return get_messages(num_msgs);
}

// Get the last few messages
string MessageBufferDumper::get_messages(const size_t num_to_dump) const
{
  ostringstream ss;

  ss << String::centre(StringTable::get(TextKeys::LATEST_MESSAGES), num_cols) << endl << endl;

  MessageBuffer mb = mm.get_message_buffer();
  size_t num = std::min<size_t>(num_to_dump, mb.size());

  for (size_t i = 0; i < num; i++)
  {
    string msg = mb.get_message(i);
    ss << msg << endl;
  }

  return ss.str();
}
