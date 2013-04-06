#include "SavageLandsEngine.hpp"
#include "XMLConfigurationReader.hpp"
#include "Class.hpp"
#include "ClassSelectionScreen.hpp"
#include "Conversion.hpp"
#include "Creature.hpp"
#include "CreatureFactory.hpp"
#include "DeitySelectionScreen.hpp"
#include "DisplayTile.hpp"
#include "FileConstants.hpp"
#include "Game.hpp"
#include "LoadGameScreen.hpp"
#include "Log.hpp"
#include "MessageManager.hpp"
#include "NamingScreen.hpp"
#include "Naming.hpp"
#include "RaceSelectionScreen.hpp"
#include "Serialization.hpp"
#include "SexSelectionScreen.hpp"
#include "TextKeys.hpp"
#include "WelcomeScreen.hpp"

using namespace std;

// State manager functionality.
EngineStateManager::EngineStateManager()
{
  current_state = ENGINE_STATE_START_NEW_GAME;
}

void EngineStateManager::set_state(const EngineStateEnum new_state)
{
  current_state = new_state;
}

EngineStateEnum EngineStateManager::get_state() const
{
  return current_state;
}

bool EngineStateManager::start_new_game() const
{
  return (current_state == ENGINE_STATE_START_NEW_GAME);
}

bool EngineStateManager::load_existing_game() const
{
  return (current_state == ENGINE_STATE_LOAD_GAME);
}

bool EngineStateManager::exit() const
{
  return (current_state == ENGINE_STATE_STOP);
}

// Core engine functionality

SavageLandsEngine::SavageLandsEngine()
{
  initialize_game_option_map();
  initialize_game_flow_map();
}

void SavageLandsEngine::initialize_game_option_map()
{
  game_option_map.insert(make_pair("a", ENGINE_STATE_START_NEW_GAME));
  game_option_map.insert(make_pair("b", ENGINE_STATE_LOAD_GAME));
  game_option_map.insert(make_pair("z", ENGINE_STATE_STOP));
}

void SavageLandsEngine::initialize_game_flow_map()
{
  game_flow_functions.insert(make_pair(ENGINE_STATE_START_NEW_GAME, &SavageLandsEngine::process_new_game));
  game_flow_functions.insert(make_pair(ENGINE_STATE_LOAD_GAME, &SavageLandsEngine::process_load_game));
  game_flow_functions.insert(make_pair(ENGINE_STATE_STOP, &SavageLandsEngine::process_exit_game));
}

void SavageLandsEngine::start()
{
  Game& game = Game::instance();

  // JCD FIXME: Eventually make this value read from its own ini/configuration file.
  game.set_sid_ini_filename("savagelandstext_en.ini");
  game.actions.reload_scripts_and_sids();

  if (state_manager.start_new_game())
  {
    setup_game();
  }

  setup_player_and_world();
    
  if (!state_manager.exit())
  {
    game.go();
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
  Game& game = Game::instance();
  
  XMLConfigurationReader reader(FileConstants::XML_CONFIGURATION_FILE);

  // Read the races, classes, and items from the configuration file.
  // Items need to be read first so that each class's default items can be loaded.
  // Custom maps are read last because they rely on creatures (which rely on races
  // and classes), and items.
  game.set_display(display);

  pair<ItemMap, GenerationValuesMap> items = reader.get_items();
  game.set_items(items.first);
  game.set_item_generation_values(items.second);

  DeityMap deities = reader.get_deities();      
  game.set_deities(deities);

  RaceMap races = reader.get_races();
  game.set_races(races);

  ClassMap classes = reader.get_classes();
  game.set_classes(classes);

  pair<CreatureMap, CreatureGenerationValuesMap> creatures = reader.get_creatures();    
  game.set_creatures(creatures.first);
  game.set_creature_generation_values(creatures.second);

  SpellMap spells = reader.get_spells();
  game.set_spells(spells);

  vector<DisplayTile> tile_info = reader.get_tile_info();
  game.set_tile_display_info(tile_info);

  vector<MapPtr> custom_maps = reader.get_custom_maps(FileConstants::CUSTOM_MAPS_DIRECTORY, FileConstants::CUSTOM_MAPS_PATTERN);
  game.set_custom_maps(custom_maps);
    
  // Set up the message manager also.
  MessageManager& manager = MessageManager::instance();
  manager.set_display(display);
}

// Create the player
void SavageLandsEngine::setup_player_and_world()
{
  bool done = false;

  while (!done)
  {
    WelcomeScreen welcome(display);
    string game_option = welcome.display();

    done = process_game_option(game_option);
  }
}

// Process the game option.
bool SavageLandsEngine::process_game_option(const string& game_option)
{
  EngineStateEnum engine_state = game_option_map[game_option];
  state_manager.set_state(engine_state);

  map<EngineStateEnum, bool (SavageLandsEngine::*)(void)>::iterator g_it = game_flow_functions.find(engine_state);
  return (this->*(g_it->second))();
}

// Process a new game command
bool SavageLandsEngine::process_new_game()
{
  Game& game = Game::instance();

  string name;
  CreatureSex sex;
    
  DeityMap deities = game.get_deities_ref();
  RaceMap  races   = game.get_races_ref();
  ClassMap classes = game.get_classes_ref();

  bool user_and_character_exist = true;
  string warning_message;

  while (user_and_character_exist)
  {
    NamingScreen naming(display, warning_message);
    name = naming.display();
    name = Naming::clean_name(name);

    if (Serialization::does_savefile_exist_for_user_and_character(Environment::get_user_name(), name))
    {
      warning_message = StringTable::get(TextKeys::CHARACTER_ALREADY_EXISTS);
    }
    else
    {
      user_and_character_exist = false;
    }
  }

  SexSelectionScreen sex_selection(display);
  sex = static_cast<CreatureSex>(String::to_int(sex_selection.display()));

  RaceSelectionScreen race_selection(display);
  string race_index = race_selection.display();
  int race_idx = Char::keyboard_selection_char_to_int(race_index.at(0));
  string selected_race_id = Integer::to_string_key_at_given_position_in_rc_map(races, race_idx);

  ClassSelectionScreen class_selection(display);
  string class_index = class_selection.display();
  int class_idx = Char::keyboard_selection_char_to_int(class_index.at(0));
  string selected_class_id = Integer::to_string_key_at_given_position_in_rc_map(classes, class_idx);

  RacePtr selected_race = races[selected_race_id];
  DeitySelectionScreen deity_selection(display, selected_race);
  string deity_index = deity_selection.display();
  int deity_idx = Char::keyboard_selection_char_to_int(deity_index.at(0));
  string selected_deity_id;

  if (selected_race)
  {
    vector<string> deity_ids = selected_race->get_initial_deity_ids();
    for (uint i = 0; i < deity_ids.size(); i++)
    {
      if (static_cast<int>(i) == deity_idx)
      {
        selected_deity_id = deity_ids.at(i);
      }
    }

    CreaturePtr player = CreatureFactory::create_by_race_and_class(game.get_action_manager_ref(), selected_race_id, selected_class_id, name, sex, selected_deity_id);
    player->set_is_player(true, controller);  

    game.create_new_world(player); 
  }

  return true;
}

// Process a load game command
bool SavageLandsEngine::process_load_game()
{
  bool result = false;

  LoadGameScreen load_game(display);
  string option = load_game.display();

  string filename = load_game.get_file_name(option);

  if (!filename.empty())
  {
    SerializationReturnCode src = Serialization::load(filename);

    if (src == SERIALIZATION_OK)
    {
      Serialization::delete_savefile(filename);
      result = true;
    }
  }

  return result;
}

// Exit
bool SavageLandsEngine::process_exit_game()
{
  return true;
}