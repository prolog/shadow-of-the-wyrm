#include "MessageManager.hpp"
#include "SearchActionManager.hpp"

using std::string;

SearchActionManager::SearchActionManager()
{
}

ActionCostValue SearchActionManager::search(CreaturePtr creature)
{
  if (creature && creature->get_is_player())
  {
    MessageManager& manager = MessageManager::instance();
    string search_message = StringTable::get(ActionTextKeys::ACTION_SEARCH);

    manager.add_new_message(search_message);
    manager.send();

    // JCD FIXME: Add actual search to see if anything hidden was spotted.
  }
  
  return get_action_cost_value();
}

ActionCostValue SearchActionManager::get_action_cost_value() const
{
  return 1;
}
