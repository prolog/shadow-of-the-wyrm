#include "AdditionalEffectMessage.hpp"
#include "MessageManagerFactory.hpp"
#include "Serialize.hpp"
#include "StringTable.hpp"

using namespace std;

AdditionalEffectMessage::AdditionalEffectMessage(const string& effect_msg_sid)
: effect_message_sid(effect_msg_sid)
{
}

// Add the additional effect message
void AdditionalEffectMessage::add_effect_message(CreaturePtr creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
  string message = StringTable::get(effect_message_sid);

  manager.add_new_message(message);
  manager.send();
}

