#include "ActionTextKeys.hpp"
#include "EffectFactory.hpp"
#include "ItemIdentifier.hpp"
#include "MessageManagerFactory.hpp"
#include "ReadStrategy.hpp"

using namespace std;

void ReadStrategy::add_read_message(const pair<string, string>& player_and_monster_read_message_sids, CreaturePtr creature, ReadablePtr readable, const ItemIdentifier& item_id)
{
  if (creature && readable)
  {
    EffectPtr effect = EffectFactory::create_effect(readable->get_effect_type());
    string player_message_sid = player_and_monster_read_message_sids.first;
    string monster_message_sid = player_and_monster_read_message_sids.second;

    // Get "You/monster reads a scroll/spellbook labelled "FOO BAR"" message
    string read_message = ActionTextKeys::get_read_message(player_message_sid, monster_message_sid, creature->get_description_sid(), item_id.get_appropriate_usage_description(readable), creature->get_is_player());
    
    // Display an appropriate message
    IMessageManager& manager = MessageManagerFactory::instance(creature);
    
    manager.add_new_message(read_message);
    manager.send();
  }
}

