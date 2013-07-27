#include "ActionTextKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "SearchAction.hpp"

using std::string;

SearchAction::SearchAction()
{
}

ActionCostValue SearchAction::search(CreaturePtr creature)
{
  if (creature && creature->get_is_player())
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature);
    string search_message = StringTable::get(ActionTextKeys::ACTION_SEARCH);

    manager.add_new_message(search_message);
    manager.send();

    // JCD FIXME: Add actual search to see if anything hidden was spotted.
  }
  
  return get_action_cost_value();
}

ActionCostValue SearchAction::get_action_cost_value() const
{
  return 1;
}
