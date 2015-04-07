#include "global_prototypes.hpp"
#include "MessageManagerFactory.hpp"
#include "ExperienceAction.hpp"

using std::string;

ExperienceAction::ExperienceAction()
{
}

ActionCostValue ExperienceAction::experience() const
{
  IMessageManager& manager = MessageManagerFactory::instance();
  
  // ...
    
  CreaturePtr nullc;
  return get_action_cost_value(nullc);
}

ActionCostValue ExperienceAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

