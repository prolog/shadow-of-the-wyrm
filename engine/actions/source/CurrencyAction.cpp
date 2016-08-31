#include "CurrencyAction.hpp"
#include "MessageManagerFactory.hpp"
#include "TextMessages.hpp"

using std::string;

ActionCostValue CurrencyAction::count_currency(CreaturePtr creature)
{
  if (creature)
  {
    uint currency_quantity = creature->get_inventory()->count_currency();
    add_currency_message_if_necessary(creature, currency_quantity);    
  }

  return get_action_cost_value(creature);
}

void CurrencyAction::add_currency_message_if_necessary(CreaturePtr creature, const uint currency_quantity)
{
  IMessageManager& manager = MessageManagerFactory::instance(creature, creature && creature->get_is_player());
    
  string currency_message = TextMessages::get_currency_amount_message(currency_quantity);
      
  manager.add_new_message(currency_message);
  manager.send();
}

ActionCostValue CurrencyAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0; // Always costs nothing to double-check currency.
}
