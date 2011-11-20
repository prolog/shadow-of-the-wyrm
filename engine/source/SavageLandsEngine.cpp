#include "SavageLandsEngine.hpp"
#include "XMLConfigurationReader.hpp"
#include "Class.hpp"
#include "ClassSelectionScreen.hpp"
#include "Conversion.hpp"
#include "Game.hpp"
#include "NamingScreen.hpp"
#include "RaceSelectionScreen.hpp"
#include "WelcomeScreen.hpp"

using namespace std;

// State manager functionality.
EngineStateManager::EngineStateManager()
{
  current_state = ENGINE_STATE_START;
}

bool EngineStateManager::continue_execution() const
{
  return (current_state != ENGINE_STATE_STOP);
}

// Core engine functionality

// JCD FIXME refactor
SavageLandsEngine::SavageLandsEngine()
{
}

// The SavageLandsEngine is responsible for the deletion of the Game object.  The Game should
// not be deleted anywhere else!
SavageLandsEngine::~SavageLandsEngine()
{
  Game* game_instance = Game::get_instance();
  delete game_instance;
}

void SavageLandsEngine::start()
{
  string name;
  XMLConfigurationReader reader("data/SavageLands.xml");

  Game* game = Game::get_instance();

  if (game)
  {
    // Read the races and classes from the configuration file.
    RaceMap races = reader.get_races();
    ClassMap classes = reader.get_classes();

    game->set_races(races);
    game->set_classes(classes);

    WelcomeScreen welcome(display);
    welcome.display();

    NamingScreen naming(display);
    name = naming.display();

    RaceSelectionScreen race_selection(display);
    string race_index = race_selection.display();
    int race_idx = String::to_int(race_index);
    string selected_race_id;

    // JCD FIXME

    int current_idx = 0;
    for (RaceMap::iterator race_it = races.begin(); race_it != races.end(); race_it++)
    {
      if (current_idx == race_idx)
      {
        selected_race_id = race_it->first;
        break;
      }

      current_idx++;
    }

    ClassSelectionScreen class_selection(display);
    string class_index = class_selection.display();
    int class_idx = String::to_int(class_index);
  }
  else
  {
    // Error out here!
  }
}

void SavageLandsEngine::set_display(DisplayPtr new_display)
{
  display = new_display;
}
