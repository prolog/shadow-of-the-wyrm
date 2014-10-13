#include "DeityDecisionImplications.hpp"

using std::string;

DeityDecisionImplications::DeityDecisionImplications()
: piety_loss(0)
{
}

DeityDecisionImplications::DeityDecisionImplications(const int new_piety_loss, const string new_message_sid)
: piety_loss(new_piety_loss), message_sid(new_message_sid)
{
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
