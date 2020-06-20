#include <boost/algorithm/string.hpp>
#include "ActionTextKeys.hpp"
#include "BestiaryAction.hpp"
#include "Conversion.hpp"
#include "CreatureProperties.hpp"
#include "Game.hpp"
#include "MessageManagerFactory.hpp"
#include "ScreenTitleTextKeys.hpp"
#include "RaceManager.hpp"
#include "StringTable.hpp"
#include "TextFormatSpecifiers.hpp"
#include "TextKeys.hpp"
#include "TextDisplayScreen.hpp"

using namespace std;

BestiaryAction::BestiaryAction()
{
}

ActionCostValue BestiaryAction::display_creature_information(CreaturePtr creature, const string& creature_search_text, CreaturePtr bestiary_creature_instance) const
{
  string search_text = creature_search_text;
  IMessageManager& manager = MM::instance(MessageTransmit::SELF, creature, creature && creature->get_is_player());

  // If we need to display creature information, prompt for some creature
  // details.
  if (creature_search_text.empty())
  {
    // If the creature previously searched the bestiary, show that search text
    // in the message - hitting enter should use that!
    string last_search_text = creature->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_LAST_BESTIARY_SEARCH);

    string prompt_message = ActionTextKeys::get_bestiary_search_message(last_search_text);

    search_text = manager.add_new_message_with_prompt(prompt_message);
    manager.send();

    manager.clear_if_necessary();

    if (search_text.empty())
    {
      search_text = last_search_text;
    }

    // Update the "monster memory"
    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_LAST_BESTIARY_SEARCH, search_text);
  }

  CreaturePtr beast = bestiary_creature_instance;
  
  if (beast == nullptr)
  {
    beast = get_bestiary_creature(search_text);
  }

  if (beast)
  {
    display_bestiary_information(beast);
  }
  else
  {
    string no_such_creature = StringTable::get(ActionTextKeys::ACTION_BESTIARY_NO_SUCH_CREATURE_EXISTS);
    manager.add_new_message(no_such_creature);
    manager.send();
  }

  return get_action_cost_value(creature);
}

// Showing creature info is always free.
ActionCostValue BestiaryAction::get_action_cost_value(CreaturePtr creature) const
{
  return 0;
}

// Figure out what creature best matches the search text.  This may not be
// anything - in that case, the CreaturePtr will be null.
CreaturePtr BestiaryAction::get_bestiary_creature(const string& search_text) const
{
  // We haven't found anything - return a null CreaturePtr.
  CreaturePtr beast;

  Game& game = Game::instance();

  string short_description;
  CreatureMap creature_map = game.get_creatures_ref();
  vector<CreaturePtr> partial_matches;

  for(const CreatureMap::value_type& creature_pair : creature_map)
  {
    // If it's an exact match, use this creature.
    short_description = StringTable::get(creature_pair.second->get_short_description_sid());

    if (boost::iequals(search_text, short_description))
    {
      beast = creature_pair.second;
      break;
    }
    // If it's an inexact match, add it to the partial matches.
    else if (boost::ifind_first(StringRange(short_description.begin(), short_description.end()), 
                                StringRange(search_text.begin(), search_text.end())))
    {
      partial_matches.push_back(creature_pair.second);
    }
  }

  // If we've already found an exact match, use that.
  if (!beast)
  {
    // If we haven't found an exact match, have we found a partial match?
    if (!partial_matches.empty())
    {
      beast = partial_matches.at(0);
    }
  }

  return beast;
}

// Display the information from the bestiary in a text screen.
void BestiaryAction::display_bestiary_information(CreaturePtr creature) const
{
  if (creature)
  {
    Game& game = Game::instance();
    TextDisplayFormatter tdf;

    string bestiary_title_sid = ScreenTitleTextKeys::SCREEN_TITLE_BESTIARY;
    vector<pair<Colour, string>> bestiary_text;

    // Display the symbol
    Symbol s = creature->get_symbol();
    deque<Symbol> symbols;
    symbols.push_back(s);

    uint width = game.get_display()->get_width();
    bestiary_text.push_back(make_pair(s.get_colour(), String::centre(TextFormatSpecifiers::SYMBOL, width)));

    // Display the creature short description
    bestiary_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));
    bestiary_text.push_back(make_pair(Colour::COLOUR_WHITE, StringTable::get(creature->get_short_description_sid())));

    // Display all the possible races (when searching) or the specific race
    // (when looking at a particular creature).
    display_race_information(bestiary_text, tdf, creature);

    // Display the creature's details.
    bestiary_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));
    vector<string> text_details = tdf.format_text(StringTable::get(creature->get_text_details_sid()));
    
    for(const string& line_of_text : text_details)
    {
      bestiary_text.push_back(make_pair(Colour::COLOUR_WHITE, line_of_text));
    }

    TextDisplayScreen tds(game.get_display(), bestiary_title_sid, bestiary_text, false, symbols);
    tds.display();
  }
}

void BestiaryAction::display_race_information(vector<pair<Colour, string>>& bestiary_text, const TextDisplayFormatter& tdf, CreaturePtr creature) const
{
  if (creature != nullptr)
  {
    // Display race details. If the race id is comma-separated, we're working
    // with a range of possible race IDs (for creatures that can be more than
    // one race).
    string race_id = creature->get_race_id();
    if (!race_id.empty())
    {
      RaceManager rm;
      vector<string> race_ids = String::create_string_vector_from_csv_string(race_id);

      if (!race_ids.empty())
      {
        bestiary_text.push_back(make_pair(Colour::COLOUR_WHITE, separator));

        string race_info_sid = TextKeys::RACE;
        size_t race_id_sz = race_ids.size();

        if (race_id_sz > 1)
        {
          race_info_sid = TextKeys::RACES;
        }

        ostringstream ss;
        ss << StringTable::get(race_info_sid) << ": ";

        for (size_t i = 0; i < race_id_sz; i++)
        {
          string cur_race_id = race_ids.at(i);
          Race* race = rm.get_race(cur_race_id);

          if (race != nullptr)
          {
            ss << StringTable::get(race->get_race_name_sid());
          }

          if (i < race_id_sz - 1)
          {
            ss << ", ";
          }
        }

        vector<string> race_details = tdf.format_text(ss.str());

        for (const string& race_line : race_details)
        {
          bestiary_text.push_back(make_pair(Colour::COLOUR_WHITE, race_line));
        }
      }
    }
  }
}