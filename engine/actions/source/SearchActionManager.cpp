#include "MessageManager.hpp"
#include "SearchActionManager.hpp"

using std::string;

bool SearchActionManager::search(CreaturePtr creature)
{
  bool advance_turn = true;
  
  if (creature && creature->get_is_player())
  {
    MessageManager* manager = MessageManager::instance();
    string search_message = StringTable::get(ActionTextKeys::ACTION_SEARCH);

    manager->add_new_message(search_message);
    manager->send();

    // JCD FIXME: Add actual search to see if anything hidden was spotted.
  }
  
  return advance_turn;
}

uint SearchActionManager::get_current_action_cost() const
{
  return 1;
}
