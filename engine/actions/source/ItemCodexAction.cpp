#include "ItemCodexAction.hpp"
#include "ActionTextKeys.hpp"
#include "CreatureProperties.hpp"
#include "Game.hpp"
#include "ItemTypeTextKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

const string ItemCodexAction::TEMPLATE_SIGNIFIER = "template";
const string ItemCodexAction::STRING_REPLACEMENT = "%s";

ItemCodexAction::ItemCodexAction()
{
}

// Show the details of the most applicable item, given the search.
// Looking up an item is always free.
ActionCostValue ItemCodexAction::item_details(CreaturePtr creature) const
{
  ActionCostValue acv = get_action_cost_value(creature);
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  if (creature != nullptr)
  {
    string last_search_text = creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LAST_ITEM_CODEX_SEARCH);
    string prompt_message = ActionTextKeys::get_item_codex_search_message(last_search_text);
    string search_text = manager.add_new_message_with_prompt(prompt_message);
    manager.send();

    manager.clear_if_necessary();

    if (search_text.empty())
    {
      search_text = last_search_text;
    }

    if (!search_text.empty())
    {
      // Update the creature's last search record for the item codex.
      creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_LAST_ITEM_CODEX_SEARCH, search_text);

      ItemPtr item = get_codex_item(search_text);

      if (item != nullptr)
      {
        display_codex_item(item);
      }
      else
      {
        manager.add_new_message(StringTable::get(ActionTextKeys::ACTION_ITEM_CODEX_NO_SUCH_ITEM_EXISTS));
        manager.send();
      }
    }
  }

  return acv;
}

void ItemCodexAction::display_codex_item(ItemPtr item) const
{
  if (item != nullptr)
  {
    Game& game = Game::instance();
    string separator;
    vector<pair<Colour, string>> codex_text;
    string codex_title_sid = ScreenTitleTextKeys::SCREEN_TITLE_ITEM_CODEX;
  
    uchar symbol = item->get_symbol();
    string item_type = ItemTypeTextKeys::get_item_type_description_singular(item->get_type());

    string item_symbol(1, symbol);
    Colour item_colour = item->get_colour();

    codex_text.push_back(make_pair(item_colour, item_symbol));
    codex_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));

    ostringstream desc;
    desc << StringTable::get(item->get_description_sid()) << " (" << item_type << ")";

    codex_text.push_back(make_pair(Colour::COLOUR_WHITE, desc.str()));
    codex_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));

    // Item codex description
    // ...

    TextDisplayScreen tds(game.get_display(), codex_title_sid, codex_text);
    tds.display();
  }
}

ActionCostValue ItemCodexAction::get_action_cost_value(CreaturePtr creature) const
{
  return ActionCostConstants::NO_ACTION;
}

// Find the most relevant item in the codex.  May return nullptr.
ItemPtr ItemCodexAction::get_codex_item(const string& search_text) const
{
  ItemPtr match;
  Game& game = Game::instance();

  string item_sdesc;
  ItemMap item_map = game.get_items_ref();
  vector<ItemPtr> partial_matches;

  for (const ItemMap::value_type& item_pair : item_map)
  {
    ItemPtr item = item_pair.second;
    
    if (item != nullptr)
    {
      item_sdesc = StringTable::get(item->get_description_sid());
      string item_base_id = item->get_base_id();

      // Make sure we aren't able to find template items.
      // These are items with "template" in the ID, or "%s" (a string
      // substitution) in the description.
      if ((item_sdesc.find(STRING_REPLACEMENT) != std::string::npos) || (item_base_id.find(TEMPLATE_SIGNIFIER) != std::string::npos))
      {
        continue;
      }
      // Exact match? Perfect!
      else if (boost::iequals(search_text, item_sdesc))
      {
        match = item_pair.second;
        break;
      }
      // If it's an inexact match, add it to the partial matches.
      else if (boost::ifind_first(StringRange(item_sdesc.begin(), item_sdesc.end()),
        StringRange(search_text.begin(), search_text.end())))
      {
        partial_matches.push_back(item_pair.second);
      }
    }
  }

  // If we've already found an exact match, use that.
  if (match == nullptr)
  {
    // If we haven't found an exact match, have we found a partial match?
    if (!partial_matches.empty())
    {
      match = partial_matches.at(0);
    }
  }

  return  match;
}
