#include "Conversion.hpp"
#include "IItemFilter.hpp"
#include "InventoryCommandFactory.hpp"
#include "InventoryCommandProcessor.hpp"
#include "InventoryKeyboardCommandMap.hpp"
#include "InventoryManager.hpp"
#include "InventoryScreen.hpp"
#include "InventoryTranslator.hpp"
#include "OptionsComponent.hpp"

using namespace std;

InventoryManager::InventoryManager(DisplayPtr new_display, CreaturePtr new_creature)
: display(new_display), creature(new_creature), current_page_start(0), current_page_size(0)
{
}

InventoryManager::~InventoryManager()
{
}

// If the inventory is read-only, the items can be viewed, but not selected.  This is for use in the "y" - View your inventory
// mode.  If the inventory is not read-only, items can be selected.
vector<ItemPtr> InventoryManager::manage_inventory(IInventoryPtr inv, const list<IItemFilterPtr>& base_display_filter_list, const list<IItemFilterPtr>& additional_display_filter_list, const bool inventory_is_read_only, const bool allow_multiple_selected_items)
{
  vector<ItemPtr> selected_items;
  bool manage_inv = true;
  uint cur_page = 1;

  try
  {
    if (creature)
    {
      CommandFactoryPtr command_factory    = std::make_unique<InventoryCommandFactory>();
      KeyboardCommandMapPtr kb_command_map = std::make_unique<InventoryKeyboardCommandMap>();
    
      while (manage_inv)
      {
        DisplayInventoryMap display_inventory;
      
        if (display && creature->get_is_player())
        {
          list<IItemFilterPtr> all_filters;
          all_filters.insert(all_filters.end(), base_display_filter_list.begin(), base_display_filter_list.end());
          all_filters.insert(all_filters.end(), additional_display_filter_list.begin(), additional_display_filter_list.end());

          display_inventory = InventoryTranslator::create_display_inventory(creature, inv, all_filters);
          bool user_filters = !additional_display_filter_list.empty();
          InventoryScreen is(display, creature, display_inventory, user_filters, inventory_is_read_only);

          is.set_current_page_number(cur_page);
          string inv_selection = is.display();
          cur_page = is.get_current_page_number();

          string external_id;
          int option_id = Char::keyboard_selection_char_to_int(inv_selection.at(0));
          OptionPtr op = is.get_option(option_id);
          vector<string> external_ids;

          if (op == nullptr && inv_selection == InventoryKeyboardCommandMap::SELECT_ALL)
          {
            vector<OptionPtr> options = is.get_options();

            for (OptionPtr opt : options)
            {
              if (opt != nullptr)
              {
                external_ids.push_back(opt->get_external_id());
              }
            }
          }

          else if (op != nullptr)
          {
            external_ids.push_back(op->get_external_id());
          }

          if (!inv_selection.empty())
          {
            CommandPtr inv_command = command_factory->create(inv_selection.at(0), kb_command_map->get_command_type(inv_selection));
            manage_inv = InventoryCommandProcessor::process(this, base_display_filter_list, display_inventory, external_ids, creature, inv, inv_command.get(), inventory_is_read_only, allow_multiple_selected_items, selected_items);
            is.set_current_page_number(cur_page);
          }
        }
      }
    }
  }
  catch(...)
  {
  }
  
  return selected_items;
}

ActionCostValue InventoryManager::get_action_cost_value(CreaturePtr /*cr*/) const
{
  return 1;
}
