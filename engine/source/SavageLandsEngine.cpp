#include "SavageLandsEngine.hpp"
#include "XMLConfigurationReader.hpp"
#include "Class.hpp"
#include "ClassSelectionScreen.hpp"
#include "Conversion.hpp"
#include "Creature.hpp"
#include "CreatureFactory.hpp"
#include "DeitySelectionScreen.hpp"
#include "DisplayTile.hpp"
#include "Game.hpp"
#include "Log.hpp"
#include "MessageManager.hpp"
#include "NamingScreen.hpp"
#include "Naming.hpp"
#include "RaceSelectionScreen.hpp"
#include "SexSelectionScreen.hpp"
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
  Game* game_instance = Game::instance();
  MessageManager* manager_instance = MessageManager::instance();

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
  Game* game = Game::instance();

  if (game)
  {
    setup_game();
    setup_player_and_world();
    
    game->go();
  }
  else
  {
    Log::instance()->log("Could not set up game and world.");
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

// Set up everything needed by the Game
void SavageLandsEngine::setup_game()
{
  Game* game = Game::instance();
  
  if (game)
  {
    XMLConfigurationReader reader("data/SavageLands.xml");

    // Read the races, classes, and items from the configuration file.
    // Items need to be read first so that each class's default items can be loaded.
    DeityMap deities = reader.get_deities();      
    ItemMap items = reader.get_items();
    RaceMap races = reader.get_races();
    ClassMap classes = reader.get_classes();
    pair<CreatureMap, CreatureGenerationValuesMap> creatures = reader.get_creatures();
    
    vector<DisplayTile> tile_info = reader.get_tile_info();

    game->set_display(display);
    game->set_deities(deities);
    game->set_races(races);
    game->set_classes(classes);
    game->set_items(items);
    game->set_creatures(creatures.first);
    game->set_creature_generation_values(creatures.second);
    game->set_tile_display_info(tile_info);
    
    // Set up the message manager also.
    MessageManager* manager = MessageManager::instance();

    if (manager)
    {
      manager->set_display(display);
    }
  }
}

// Create the player
void SavageLandsEngine::setup_player_and_world()
{
  Game* game = Game::instance();
  
  if (game)
  {
    string name;
    CreatureSex sex;
    
    DeityMap deities = game->get_deities_ref();
    RaceMap  races   = game->get_races_ref();
    ClassMap classes = game->get_classes_ref();

    WelcomeScreen welcome(display);
    welcome.display();

    NamingScreen naming(display);
    name = naming.display();
    name = Naming::clean_name(name);

    SexSelectionScreen sex_selection(display);
    sex = static_cast<CreatureSex>(String::to_int(sex_selection.display()));

    RaceSelectionScreen race_selection(display);
    string race_index = race_selection.display();
    int race_idx = String::to_int(race_index);
    string selected_race_id = Integer::to_string_key_at_given_position_in_map(races, race_idx);

    ClassSelectionScreen class_selection(display);
    string class_index = class_selection.display();
    int class_idx = String::to_int(class_index);
    string selected_class_id = Integer::to_string_key_at_given_position_in_map(classes, class_idx);

    RacePtr selected_race = races[selected_race_id];
    DeitySelectionScreen deity_selection(display, selected_race);
    string deity_index = deity_selection.display();
    int deity_idx = String::to_int(deity_index);
    string selected_deity_id;
    vector<string> deity_ids = selected_race->get_initial_deity_ids();
    for (uint i = 0; i < deity_ids.size(); i++)
    {
      if (static_cast<int>(i) == deity_idx)
      {
        selected_deity_id = deity_ids.at(i);
      }
    }

    CreaturePtr player = CreatureFactory::create_by_race_and_class(selected_race_id, selected_class_id, name, sex, selected_deity_id);
    player->set_is_player(true, controller);  

    game->create_new_world(player); 
  }
}
