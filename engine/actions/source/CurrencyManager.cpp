#include "CurrencyManager.hpp"
#include "MessageManager.hpp"
#include "StringConstants.hpp"

using std::string;

ActionCostValue CurrencyManager::count_currency(CreaturePtr creature)
{
  if (creature)
  {
    Inventory& inv = creature->get_inventory();
    ItemPtr item = inv.get_from_base_id(ItemIdKeys::ITEM_ID_CURRENCY);
    
    uint currency_quantity = 0;
    
    if (item)
    {
      currency_quantity = item->get_quantity();
    }

    add_currency_message_if_necessary(creature, currency_quantity);    
  }

  return get_action_cost_value();
}

void CurrencyManager::add_currency_message_if_necessary(CreaturePtr creature, const uint currency_quantity)
{
  if (creature->get_is_player())
  {
    MessageManager& manager = MessageManager::instance();
    
    string currency_message = TextMessages::get_currency_amount_message(currency_quantity);
      
    manager.add_new_message(currency_message);
    manager.send();
  }
}

ActionCostValue CurrencyManager::get_action_cost_value() const
{
  return 0; // Always costs nothing to double-check currency.
}
