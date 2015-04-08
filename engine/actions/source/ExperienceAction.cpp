#include "global_prototypes.hpp"
#include "MessageManagerFactory.hpp"
#include "ExperienceAction.hpp"

using std::string;

ExperienceAction::ExperienceAction()
{
}

ActionCostValue ExperienceAction::experience(CreaturePtr creature) const
{
  IMessageManager& manager = MessageManagerFactory::instance();
  
  if (creature != nullptr)
  {
    // ...
  }
    
  CreaturePtr nullc;
  return get_action_cost_value(nullc);
}

ActionCostValue ExperienceAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

