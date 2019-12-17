#include "ItemCodexAction.hpp"
#include "ItemIdentifier.hpp"
#include "ActionTextKeys.hpp"
#include "CodexDescriberFactory.hpp"
#include "CreatureProperties.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "Game.hpp"
#include "ItemIdentifier.hpp"
#include "ItemTextKeys.hpp"
#include "ItemTypeTextKeys.hpp"
#include "MaterialTextKeys.hpp"
#include "MessageManagerFactory.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "TextDisplayFormatter.hpp"
#include "TextDisplayScreen.hpp"
#include "TextKeys.hpp"

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
        acv = item_details(creature, item, false);
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

ActionCostValue ItemCodexAction::item_details(CreaturePtr creature, const EquipmentWornLocation ewl) const
{
  if (creature != nullptr)
  {
    ItemPtr item = creature->get_equipment().get_item(ewl);

    if (item != nullptr)
    {
      item_details(creature, item, false);
    }
  }

  return ActionCostConstants::NO_ACTION;
}

ActionCostValue ItemCodexAction::item_details(CreaturePtr creature, ItemPtr item, const bool skip_blindness_checks) const
{
  if (creature != nullptr && item != nullptr)
  {
    ItemIdentifier iid;

    if (iid.get_item_identified(item->get_base_id()))
    {
      CurrentCreatureAbilities cca;

      if (cca.can_see(creature) || skip_blindness_checks || item->get_glowing())
      {
        display_codex_item(item);
      }
    }
    else
    {
      // Assumption is that it's only ever the player calling this.
      // This is overlaid over the inventory screen, so use an alert.
      IMessageManager& manager = MM::instance();
      manager.alert(StringTable::get(ItemTextKeys::ITEM_CODEX_NO_INFORMATION_FOUND));
    }
  }

  return ActionCostConstants::NO_ACTION;
}

void ItemCodexAction::display_codex_item(ItemPtr item) const
{
  if (item != nullptr)
  {
    Game& game = Game::instance();
    CodexDescriberFactory cdf;

    CodexDescriberPtr codex_desc = cdf.create_codex_describer(item);
    string separator;
    vector<pair<Colour, string>> codex_text;

    add_symbol_and_description_to_codex(item, codex_desc.get(), separator, codex_text);
    add_synopsis_to_codex(item, codex_desc.get(), separator, codex_text);
    add_resistances_to_codex(item, codex_desc.get(), separator, codex_text);
    add_speed_details_to_codex(item, codex_desc.get(), separator, codex_text);
    add_item_details_to_codex(item, codex_desc.get(), separator, codex_text);
    add_description_to_codex(item, codex_desc.get(), separator, codex_text);

    string codex_title_sid = ScreenTitleTextKeys::SCREEN_TITLE_ITEM_CODEX;
    TextDisplayScreen tds(game.get_display(), codex_title_sid, codex_text);
    tds.display();
  }
}

void ItemCodexAction::add_symbol_and_description_to_codex(ItemPtr item, CodexDescriber* codex_desc, const string& separator, vector<pair<Colour, string>>& codex_text) const
{
  if (item != nullptr && codex_desc != nullptr)
  {
    string symbol_details = StringTable::get(ItemTextKeys::ITEM_CODEX_NOT_IDENTIFIED);
    ItemIdentifier iid;
    bool identified = iid.get_item_identified(item->get_base_id());
    Colour item_colour = Colour::COLOUR_WHITE; 

    // If the item hasn't been identified yet, note that in white.  Otherwise,
    // use the actual symbol and colour.
    if (identified)
    {
      // JCD SYMBOL SPRITESHEET FIXME
      symbol_details = item->get_symbol().get_symbol();
      item_colour = item->get_colour();
    }

    codex_text.push_back(make_pair(item_colour, symbol_details));
    codex_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));

    string item_desc = StringTable::get(item->get_description_sid());

    codex_text.push_back(make_pair(Colour::COLOUR_WHITE, item_desc));
    codex_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));
  }
}

void ItemCodexAction::add_synopsis_to_codex(ItemPtr item, CodexDescriber* codex_desc, const string& separator, vector<pair<Colour, string>>& codex_text) const
{
  if (item != nullptr && codex_desc != nullptr)
  {
    ostringstream synopsis_line;
    ItemType itype = item->get_type();
    synopsis_line << ItemTypeTextKeys::get_item_type_description_singular(itype);

    synopsis_line << " (" << MaterialTextKeys::get_material(item->get_material_type()) << ")";

    bool is_artifact = item->get_artifact();
    if (is_artifact)
    {
      synopsis_line << " - " << StringTable::get(TextKeys::ARTIFACT);
    }

    if (item->get_auto_curse())
    {
      synopsis_line << " - " << StringTable::get(TextKeys::AUTOCURSING);
    }

    string desc_synopsis_line = codex_desc->describe_for_synopsis_line();
    if (!desc_synopsis_line.empty())
    {
      synopsis_line << " - " << desc_synopsis_line;
    }

    TextDisplayFormatter tdf;

    vector<string> synopsis_lines = tdf.format_text(synopsis_line.str());
    for (const string& s_line : synopsis_lines)
    {
      codex_text.push_back(make_pair(Colour::COLOUR_WHITE, s_line));
    }

    codex_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));
  }
}

void ItemCodexAction::add_resistances_to_codex(ItemPtr item, CodexDescriber* codex_desc, const string& separator, vector<pair<Colour, string>>& codex_text) const
{
  if (item != nullptr && codex_desc != nullptr)
  {
    TextDisplayFormatter tdf;
    vector<string> resistances = tdf.format_text(codex_desc->describe_resistances());

    if (!resistances.empty())
    {
      for (const string& line_of_text : resistances)
      {
        codex_text.push_back(make_pair(Colour::COLOUR_WHITE, line_of_text));
      }

      codex_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));
    }
  }
}

void ItemCodexAction::add_speed_details_to_codex(ItemPtr item, CodexDescriber* codex_desc, const string& separator, vector<pair<Colour, string>>& codex_text) const
{
  if (item != nullptr && codex_desc != nullptr)
  {
    string speed_bonus = codex_desc->describe_speed_bonus();

    if (!speed_bonus.empty())
    {
      codex_text.push_back(make_pair(Colour::COLOUR_WHITE, speed_bonus));
      codex_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));
    }
  }
}

void ItemCodexAction::add_item_details_to_codex(ItemPtr item, CodexDescriber* codex_desc, const string& separator, vector<pair<Colour, string>>& codex_text) const
{
  if (item != nullptr && codex_desc != nullptr)
  {
    string details = codex_desc->describe_details();

    if (!details.empty())
    {
      TextDisplayFormatter tdf;
      vector<string> details_text = tdf.format_text(details);

      for (const string& detail_line : details_text)
      {
        codex_text.push_back(make_pair(Colour::COLOUR_WHITE, detail_line));
      }

      codex_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));
    }
  }
}

void ItemCodexAction::add_description_to_codex(ItemPtr item, CodexDescriber* codex_desc, const string& separator, vector<pair<Colour, string>>& codex_text) const
{
  if (item != nullptr)
  {
    // Item codex description
    TextDisplayFormatter tdf;
    vector<string> codex = tdf.format_text(StringTable::get(item->get_codex_description_sid()));

    for (const string& line_of_text : codex)
    {
      codex_text.push_back(make_pair(Colour::COLOUR_WHITE, line_of_text));
    }
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
  ItemIdentifier iid;

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
        if (iid.get_item_identified(item, true))
        {
          partial_matches.push_back(item_pair.second);
        }
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
