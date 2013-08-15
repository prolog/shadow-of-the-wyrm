#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
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
    IMessageManager& manager = MessageManagerFactory::instance(creature, true);
    CurrentCreatureAbilities cca;

    string search_message;
    
    if (cca.can_see(creature))
    {
      search_message = StringTable::get(ActionTextKeys::ACTION_SEARCH);
    }
    else
    {
      search_message = StringTable::get(ActionTextKeys::ACTION_SEARCH_BLIND);
    }


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
