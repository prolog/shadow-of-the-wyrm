#include "CurrencyAction.hpp"
#include "MessageManagerFactory.hpp"
#include "TextMessages.hpp"

using std::string;

ActionCostValue CurrencyAction::count_currency(CreaturePtr creature)
{
  if (creature)
  {
    IMessageManager& manager = MMF::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

    uint currency_quantity = creature->get_inventory()->count_currency();
    string currency_message = TextMessages::get_currency_amount_message(currency_quantity);
    manager.add_new_message(currency_message);

    uint unpaid_amount = creature->get_unpaid_amount();
    if (unpaid_amount > 0)
    {
      manager.add_new_message(TextMessages::get_unpaid_amount_message(unpaid_amount));
    }

    manager.send();
  }

  return get_action_cost_value(creature);
}

ActionCostValue CurrencyAction::get_action_cost_value(CreaturePtr /*creature*/) const
{
  return 0; // Always costs nothing to double-check balances.
}
