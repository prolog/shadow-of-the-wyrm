#include "CharacterDumpManager.hpp"
#include "CharacterDumper.hpp"
#include "FileWriter.hpp"
#include "MessageManager.hpp"

using std::string;

void CharacterDumpManager::dump_character(CreaturePtr creature)
{
  if (creature)
  {
    MessageManager* manager = MessageManager::instance();
    string name = creature->get_name();
    string dump_message = TextMessages::get_dumping_character_message(name);
    
    CharacterDumper dumper(creature);
    FileWriter file(creature->get_name());
    
    file.write(dumper.str());
    
    manager->add_new_message(dump_message);
    manager->send();
  }
}


uint CharacterDumpManager::get_current_action_cost() const
{
  return 0;
}
