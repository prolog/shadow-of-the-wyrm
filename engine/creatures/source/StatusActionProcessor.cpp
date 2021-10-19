#include "StatusActionProcessor.hpp"
#include "StatusEffectFactory.hpp"

using namespace std;

void StatusActionProcessor::process_action(CreaturePtr creature, CreatureStatusMap statuses_before_action, ActionCost action)
{
  auto s_it = statuses_before_action.find(StatusIdentifiers::STATUS_ID_TIMEWALK);

  if (s_it != statuses_before_action.end() && s_it->second.get_value() == true && action.get_cost() > 0)
  {
    StatusEffectPtr se = StatusEffectFactory::create_status_effect(creature, StatusIdentifiers::STATUS_ID_TIMEWALK, s_it->second.get_source_id());    
    se->undo_change(creature);
  }
}
