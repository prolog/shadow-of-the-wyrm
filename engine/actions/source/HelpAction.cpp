#include "global_prototypes.hpp"
#include "MessageManagerFactory.hpp"
#include "Metadata.hpp"
#include "HelpAction.hpp"

using std::string;

HelpAction::HelpAction()
{
}

ActionCostValue HelpAction::help(CreaturePtr creature) const
{
  CreaturePtr nullc;

  // Show the help screen.
  // ...

  // Based on the selected option, show additional help.
  // ...

  return get_action_cost_value(nullc);
}

ActionCostValue HelpAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

