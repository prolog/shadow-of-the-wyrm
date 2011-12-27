#include "SavageLandsEngine.hpp"
#include "XMLConfigurationReader.hpp"
#include "Class.hpp"
#include "ClassSelectionScreen.hpp"
#include "Conversion.hpp"
#include "Creature.hpp"
#include "CreatureFactory.hpp"
#include "DisplayTile.hpp"
#include "Game.hpp"
#include "MessageManager.hpp"
#include "NamingScreen.hpp"
#include "Naming.hpp"
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
  MessageManager* manager_instance = MessageManager::get_instance();

  if (game_instance)
  {
    delete game_instance;
    game_instance = NULL;
  }

  if (manager_instance)
  {
    delete manager_instance;
    manager_instance = NULL;
  }
}

void SavageLandsEngine::start()
{
  string name;
  XMLConfigurationReader reader("data/SavageLands.xml");

  Game* game = Game::get_instance();
  MessageManager* manager = MessageManager::get_instance();

  if (game && manager)
  {
    manager->set_display(display);
    {
      // Read the races and classes from the configuration file.
      RaceMap races = reader.get_races();
      ClassMap classes = reader.get_classes();
      vector<DisplayTile> tile_info = reader.get_tile_info();

      game->set_display(display);
      game->set_races(races);
      game->set_classes(classes);
      game->set_tile_display_info(tile_info);

      WelcomeScreen welcome(display);
      welcome.display();

      NamingScreen naming(display);
      name = naming.display();
      name = Naming::clean_name(name);

      RaceSelectionScreen race_selection(display);
      string race_index = race_selection.display();
      int race_idx = String::to_int(race_index);
      string selected_race_id = Integer::to_string_key_at_given_position_in_map(races, race_idx);

      ClassSelectionScreen class_selection(display);
      string class_index = class_selection.display();
      int class_idx = String::to_int(class_index);
      string selected_class_id = Integer::to_string_key_at_given_position_in_map(classes, class_idx);

      CreaturePtr player = CreatureFactory::create_by_race_and_class(selected_race_id, selected_class_id, name);
      player->set_is_player(true, controller);

      // Create world map, place player on world map.
      game->create_new_world(player);
    }

    // FIXME: Extra paren block is to destruct the menus so that the windows are released, etc.
    // Fix this up later.  Can probably be made cleaner with fn call refactoring.

    // Play!
    game->go();
  }
  else
  {
    // Error out here!
  }
}

void SavageLandsEngine::set_controller(ControllerPtr new_controller)
{
  controller = new_controller;
}

void SavageLandsEngine::set_display(DisplayPtr new_display)
{
  display = new_display;
}
