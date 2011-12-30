#include <string>
#include "RaceSelectionScreen.hpp"
#include "Game.hpp"
#include "OptionsComponent.hpp"
#include "StringConstants.hpp"
#include "TextComponent.hpp"

using namespace std;

RaceSelectionScreen::RaceSelectionScreen(DisplayPtr display)
: Menu(display)
{
  initialize();
}

// Initialize the race selection screen.  Races must have been read in, and set into the Game
// instance at this point.
//
// The Menu will return an int based on the user's selection.  This will map to a race_id, which will then map to a
// RacePtr.
void RaceSelectionScreen::initialize()
{
  Game* game_instance = Game::instance();
  RaceMap races = game_instance->get_races_ref();

  TextComponent* race_selection_text = new TextComponent(StringTable::get(TextKeys::SELECT_RACE));

  // Each option represents a player-selectable race.
  OptionsComponent* options = new OptionsComponent();

  int current_id = 0;
  for (RaceMap::iterator races_it = races.begin(); races_it != races.end(); races_it++)
  {
    string race_id = races_it->first;
    RacePtr current_race = races_it->second;

    if (current_race && options)
    {
      Option current_option;
      current_option.set_id(current_id);
      current_option.set_description(StringTable::get(current_race->get_race_name_sid()));

      options->add_option(current_option);
      options->add_option_description(StringTable::get(current_race->get_race_short_description_sid()));
      current_id++;
    }
  }

  components.push_back(race_selection_text);
  components.push_back(options);
}
