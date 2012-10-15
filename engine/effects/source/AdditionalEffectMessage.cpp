#include "AdditionalEffectMessage.hpp"
#include "MessageManager.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"

using namespace std;

AdditionalEffectMessage::AdditionalEffectMessage(const string& effect_msg_sid)
: effect_message_sid(effect_msg_sid)
{
}

// Add the additional effect message
void AdditionalEffectMessage::add_effect_message() const
{
  MessageManager* manager = MessageManager::instance();
  string message = StringTable::get(effect_message_sid);

  if (manager)
  {
    manager->add_new_message(message);
    manager->send();
  }
}

bool AdditionalEffectMessage::serialize(ostream& stream)
{
  Serialize::write_string(stream, effect_message_sid);

  return true;
}

bool AdditionalEffectMessage::deserialize(istream& stream)
{
  Serialize::read_string(stream, effect_message_sid);

  return true;
}