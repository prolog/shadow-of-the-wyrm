#include "CharacterDumpAction.hpp"
#include "CharacterDumper.hpp"
#include "FileWriter.hpp"
#include "MessageManagerFactory.hpp"
#include "TextMessages.hpp"

using std::string;

CharacterDumpAction::CharacterDumpAction()
{
}

ActionCostValue CharacterDumpAction::dump_character(CreaturePtr creature)
{
  if (creature)
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature);
    string name = creature->get_name();
    string dump_message = TextMessages::get_dumping_character_message(name);
    
    CharacterDumper dumper(creature);
    FileWriter file(creature->get_name());
    
    file.write(dumper.str());
    
    manager.add_new_message(dump_message);
    manager.send();
  }
  
  return get_action_cost_value();
}


ActionCostValue CharacterDumpAction::get_action_cost_value() const
{
  return 0;
}
