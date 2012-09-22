#include "AdditionalEffectMessage.hpp"
#include "MessageManager.hpp"
#include "StringTable.hpp"

using std::string;

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
