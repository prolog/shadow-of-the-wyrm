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
  Game* game_instance = Game::get_instance();
  RaceMap races = game_instance->get_races_ref();

  TextComponent race_selection_text(TextKeys::SELECT_RACE);

  // Each option represents a player-selectable race.
  OptionsComponent options;

  for (RaceMap::iterator races_it = races.begin(); races_it != races.end(); races_it++)
  {
    string race_id = races_it->first;
    RacePtr current_race = races_it->second;
  }
}
