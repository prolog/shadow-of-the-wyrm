#include "ActionTextKeys.hpp"
#include "EffectFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManager.hpp"
#include "ReadStrategy.hpp"

using namespace std;

void ReadStrategy::add_read_message(CreaturePtr creature, ReadablePtr readable, const ItemIdentifier& item_id)
{
  if (creature && readable)
  {
    EffectPtr effect = EffectFactory::create_effect(readable->get_effect_type());
    
    // Get "You/monster reads a scroll/spellbook labelled "FOO BAR"" message
    string read_message = ActionTextKeys::get_read_message(creature->get_description_sid(), item_id.get_appropriate_usage_description(readable), creature->get_is_player());
    
    // Display an appropriate message
    MessageManager& manager = MessageManager::instance();
    
    manager.add_new_message(read_message);
    manager.send();
  }
}

