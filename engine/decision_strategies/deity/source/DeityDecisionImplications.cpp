#include "DeityDecisionImplications.hpp"
#include "AlignmentCalculator.hpp"
#include "ClassManager.hpp"
#include "CreatureUtils.hpp"
#include "ReligionManager.hpp"

using std::string;

DeityDecisionImplications::DeityDecisionImplications()
: piety_loss(0)
{
}

DeityDecisionImplications::DeityDecisionImplications(const int new_piety_loss, const string new_message_sid)
: piety_loss(new_piety_loss), message_sid(new_message_sid)
{
}

// Alter the creature's piety as a result of the sacrifice.
int DeityDecisionImplications::adjust_creature_piety(CreaturePtr creature, FeaturePtr feature)
{
  int piety_gain = get_piety_gain();

  // Get the deity and the creature's status with that deity.
  ReligionManager rm;
  ClassManager cm;

  Religion& religion = creature->get_religion_ref();
  string deity_id = religion.get_active_deity_id();
  DeityStatus status = religion.get_deity_status(deity_id);

  status.increment_piety(piety_gain);
  religion.set_deity_status(deity_id, status);

  AlignmentCalculator ac;
  int new_alignment = ac.calculate_alignment_for_sacrifice_on_coaligned_altar(creature->get_alignment().get_alignment(), feature->get_alignment_range());
  CreatureUtils::handle_alignment_change(creature, new_alignment);

  return piety_gain;
}


void DeityDecisionImplications::set_piety_loss(const int new_piety_loss)
{
  piety_loss = new_piety_loss;
}

int DeityDecisionImplications::get_piety_loss() const
{
  return piety_loss;
}

int DeityDecisionImplications::get_piety_gain() const
{
  return (piety_loss * -1);
}

void DeityDecisionImplications::set_message_sid(const string& new_message_sid)
{
  message_sid = new_message_sid;
}

string DeityDecisionImplications::get_message_sid() const
{
  return message_sid;
}
