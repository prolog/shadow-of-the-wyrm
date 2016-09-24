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
    IMessageManager& manager = MM::instance();
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
  
  return get_action_cost_value(creature);
}

ActionCostValue SearchAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}
