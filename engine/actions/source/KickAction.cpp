#include "ActionTextKeys.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "MessageManagerFactory.hpp"
#include "KickAction.hpp"

using std::string;

KickAction::KickAction()
{
}

ActionCostValue KickAction::kick(CreaturePtr creature)
{
  if (creature)
  {
    IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());

    CurrentCreatureAbilities cca;

    string kick_msg;
    
    if (cca.can_move(creature))
    {
    }
    else
    {
    }
  }
  
  return get_action_cost_value(creature);
}

ActionCostValue KickAction::get_action_cost_value(CreaturePtr creature) const
{
  return 1;
}

