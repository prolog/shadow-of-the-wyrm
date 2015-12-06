#include "ShadowOfTheWyrmEngine.hpp"
#include "XMLConfigurationReader.hpp"
#include "Class.hpp"
#include "ClassSelectionScreen.hpp"
#include "Conversion.hpp"
#include "Creature.hpp"
#include "CreatureFactory.hpp"
#include "CreatureUtils.hpp"
#include "DeitySelectionScreen.hpp"
#include "DisplaySettings.hpp"
#include "DisplayTile.hpp"
#include "FileConstants.hpp"
#include "Game.hpp"
#include "ItemDescriptionRandomizer.hpp"
#include "ItemIdentifier.hpp"
#include "LoadGameScreen.hpp"
#include "Log.hpp"
#include "MessageManagerFactory.hpp"
#include "NamingScreen.hpp"
#include "Naming.hpp"
#include "RaceSelectionScreen.hpp"
#include "RNG.hpp"
#include "ScriptConstants.hpp"
#include "Serialization.hpp"
#include "Settings.hpp"
#include "SexSelectionScreen.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "WelcomeScreen.hpp"

using namespace std;

// State manager functionality.
EngineStateManager::EngineStateManager()
{
  current_state = EngineStateEnum::ENGINE_STATE_START_NEW_GAME;
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
  return (current_state == EngineStateEnum::ENGINE_STATE_START_NEW_GAME);
}

bool EngineStateManager::start_new_game_random() const
{
  return (current_state == EngineStateEnum::ENGINE_STATE_START_NEW_GAME_RANDOM);
}

bool EngineStateManager::load_existing_game() const
{
  return (current_state == EngineStateEnum::ENGINE_STATE_LOAD_GAME);
}

bool EngineStateManager::exit() const
{
  return (current_state == EngineStateEnum::ENGINE_STATE_STOP);
}

// Core engine functionality

ShadowOfTheWyrmEngine::ShadowOfTheWyrmEngine()
{
  initialize_game_option_map();
  initialize_game_flow_map();
}

void ShadowOfTheWyrmEngine::initialize_game_option_map()
{
  game_option_map = GameOptionMap{ { "a", EngineStateEnum::ENGINE_STATE_START_NEW_GAME },
                                   { "b", EngineStateEnum::ENGINE_STATE_START_NEW_GAME_RANDOM },
                                   { "c", EngineStateEnum::ENGINE_STATE_LOAD_GAME },
                                   { "z", EngineStateEnum::ENGINE_STATE_STOP } };
}

void ShadowOfTheWyrmEngine::initialize_game_flow_map()
{
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_START_NEW_GAME, &ShadowOfTheWyrmEngine::process_new_game));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_START_NEW_GAME_RANDOM, &ShadowOfTheWyrmEngine::process_new_game_random));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_LOAD_GAME, &ShadowOfTheWyrmEngine::process_load_game));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_STOP, &ShadowOfTheWyrmEngine::process_exit_game));
}

void ShadowOfTheWyrmEngine::start(const Settings& settings)
{
  Game& game = Game::instance();

  game.set_settings(settings);
  game.actions.reload_scripts_and_sids();

  if (state_manager.start_new_game())
  {
    setup_display(settings);
    setup_game();
  }

  setup_player_and_world();
    
  if (!state_manager.exit())
  {
    game.go();
  }
}

void ShadowOfTheWyrmEngine::set_controller(ControllerPtr new_controller)
{
  controller = new_controller;
}

void ShadowOfTheWyrmEngine::set_display(DisplayPtr new_display)
{
  display = new_display;
}

// Set up the Display based on the ini settings.
void ShadowOfTheWyrmEngine::setup_display(const Settings& settings)
{
  if (display)
  {
    // Use newfangled colour?  Or traditional mono?
    string colour = DisplaySettings::DISPLAY_SETTING_COLOUR;
    display->set_property(colour, settings.get_setting(colour));
  }
}

// Set up everything needed by the Game
void ShadowOfTheWyrmEngine::setup_game()
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

  map<string, string> scripts = reader.get_scripts();
  game.set_scripts(scripts);

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

  vector<TrapPtr> trap_info = reader.get_trap_info();
  game.set_trap_info(trap_info);

  vector<MapPtr> custom_maps = reader.get_custom_maps(FileConstants::CUSTOM_MAPS_DIRECTORY, FileConstants::CUSTOM_MAPS_PATTERN);
  game.set_custom_maps(custom_maps);
    
  // Set up the message manager also.
  IMessageManager& manager = MessageManagerFactory::instance();
  manager.set_display(display);
}

// Create the player
void ShadowOfTheWyrmEngine::setup_player_and_world()
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
bool ShadowOfTheWyrmEngine::process_game_option(const string& game_option)
{
  EngineStateEnum engine_state = game_option_map[game_option];
  state_manager.set_state(engine_state);

  map<EngineStateEnum, bool (ShadowOfTheWyrmEngine::*)(void)>::iterator g_it = game_flow_functions.find(engine_state);
  return (this->*(g_it->second))();
}

// Process a new game command, random character
bool ShadowOfTheWyrmEngine::process_new_game_random()
{
  CharacterCreationDetails ccd;

  // Random sex
  CreatureSex sex = static_cast<CreatureSex>(RNG::range(static_cast<int>(CreatureSex::CREATURE_SEX_MALE), static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE)));

  // Random playable race id
  RacePtr race = CreatureUtils::get_random_user_playable_race();

  // Random playable class id
  ClassPtr cur_class = CreatureUtils::get_random_user_playable_class();

  // Random allowable deity
  DeityPtr deity = CreatureUtils::get_random_deity_for_race(race);

  if (race && cur_class && deity)
  {
    ccd.set_sex(sex);
    ccd.set_race_id(race->get_race_id());
    ccd.set_class_id(cur_class->get_class_id());
    ccd.set_deity_id(deity->get_id());
  }

  // Get name, and start.
  return process_name_and_start(ccd);
}

// Process a new game command
bool ShadowOfTheWyrmEngine::process_new_game()
{
  Game& game = Game::instance();
  CreatureSex sex = CreatureSex::CREATURE_SEX_MALE;
    
  DeityMap deities = game.get_deities_ref();
  RaceMap  races   = game.get_races_ref();
  ClassMap classes = game.get_classes_ref();
  
  Option opt;
  SexSelectionScreen sex_selection(display);
  string sex_selection_s = sex_selection.display();
  int keyboard_selection = Char::keyboard_selection_char_to_int(sex_selection_s.at(0));

  if (opt.is_random_option(sex_selection_s.at(0)))
  {
    sex = static_cast<CreatureSex>(RNG::range(static_cast<int>(CreatureSex::CREATURE_SEX_MALE), static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE)));
  }
  else
  {
    sex = static_cast<CreatureSex>(keyboard_selection);
  }

  RaceSelectionScreen race_selection(display);
  string race_index = race_selection.display();
  string selected_race_id;

  if (opt.is_random_option(race_index.at(0)))
  {
    RacePtr random_race = CreatureUtils::get_random_user_playable_race();

    if (random_race != nullptr)
    {
      selected_race_id = random_race->get_race_id();
    }
  }
  else
  {
    int race_idx = Char::keyboard_selection_char_to_int(race_index.at(0));
    selected_race_id = Integer::to_string_key_at_given_position_in_rc_map(races, race_idx);
  }

  ClassSelectionScreen class_selection(display);
  string class_index = class_selection.display();
  string selected_class_id;

  if (opt.is_random_option(class_index.at(0)))
  {
    ClassPtr cur_class = CreatureUtils::get_random_user_playable_class();

    if (cur_class != nullptr)
    {
      selected_class_id = cur_class->get_class_id();
    }
  }
  else
  {
    int class_idx = Char::keyboard_selection_char_to_int(class_index.at(0));
    selected_class_id = Integer::to_string_key_at_given_position_in_rc_map(classes, class_idx);
  }

  RacePtr selected_race = races[selected_race_id];
  ClassPtr selected_class = classes[selected_class_id];

  DeitySelectionScreen deity_selection(display, selected_race);
  string deity_index = deity_selection.display();
  string selected_deity_id;

  if (opt.is_random_option(deity_index.at(0)))
  {
    DeityPtr deity = CreatureUtils::get_random_deity_for_race(selected_race);

    if (deity != nullptr)
    {
      selected_deity_id = deity->get_id();
    }
  }
  else
  {
    int deity_idx = Char::keyboard_selection_char_to_int(deity_index.at(0));

    vector<string> deity_ids = selected_race->get_initial_deity_ids();
    for (uint i = 0; i < deity_ids.size(); i++)
    {
      if (static_cast<int>(i) == deity_idx)
      {
        selected_deity_id = deity_ids.at(i);
      }
    }
  }

  CharacterCreationDetails ccd(sex, selected_race_id, selected_class_id, selected_deity_id);
  return process_name_and_start(ccd);
}

bool ShadowOfTheWyrmEngine::process_name_and_start(const CharacterCreationDetails& ccd)
{
  Game& game = Game::instance();

  RaceMap  races = game.get_races_ref();
  ClassMap classes = game.get_classes_ref();
  DeityMap deities = game.get_deities_ref();

  RacePtr selected_race = races.at(ccd.get_race_id());
  ClassPtr selected_class = classes.at(ccd.get_class_id());
  DeityPtr deity = deities.at(ccd.get_deity_id());
  string name;

  bool user_and_character_exist = true;
  string creature_synopsis = TextMessages::get_sex(ccd.get_sex()) + " " + StringTable::get(selected_race->get_race_name_sid()) + " " + StringTable::get(selected_class->get_class_name_sid()) + ", " + StringTable::get(deity->get_name_sid());
  string warning_message;

  while (user_and_character_exist)
  {
    string default_name = game.get_settings_ref().get_setting("default_name");
    NamingScreen naming(display, creature_synopsis, warning_message);
    name = naming.display();

    if (name.empty())
    {
      name = default_name;
    }

    name = Naming::clean_name_or_use_default(name, ccd.get_sex());

    if (Serialization::does_savefile_exist_for_user_and_character(Environment::get_user_name(), name))
    {
      warning_message = StringTable::get(TextKeys::CHARACTER_ALREADY_EXISTS);
    }
    else
    {
      user_and_character_exist = false;
    }
  }

  CreatureFactory cf;
  CreaturePtr player = cf.create_by_race_and_class(game.get_action_manager_ref(), ccd.get_race_id(), ccd.get_class_id(), name, ccd.get_sex(), ccd.get_deity_id());
  player->set_is_player(true, controller);

  // Identify the player's equipment and inventory.  If any equipment is
  // cursed, make it uncursed.
  ItemIdentifier item_id;
  item_id.set_possessions_identified(player);
  EquipmentMap eq_map = player->get_equipment().get_equipment();

  for (const EquipmentMap::value_type& eq_pair : eq_map)
  {
    ItemPtr item = eq_pair.second;
    if (item && item->get_status() == ItemStatus::ITEM_STATUS_CURSED) item->set_status(ItemStatus::ITEM_STATUS_UNCURSED);
  }

  vector<ItemType> item_types{ ItemType::ITEM_TYPE_SCROLL, ItemType::ITEM_TYPE_WAND, ItemType::ITEM_TYPE_STAFF, ItemType::ITEM_TYPE_SPELLBOOK, ItemType::ITEM_TYPE_RING, ItemType::ITEM_TYPE_POTION, ItemType::ITEM_TYPE_AMULET };
  ItemDescriptionRandomizer item_randomizer(item_types);
  item_randomizer.randomize(game.items);

  game.create_new_world(player);

  // Run the "special day" script.
  game.get_script_engine_ref().execute(game.get_script(ScriptConstants::SPECIAL_DAY_SCRIPT));

  return true;
}

// Process a load game command
bool ShadowOfTheWyrmEngine::process_load_game()
{
  bool result = false;

  LoadGameScreen load_game(display);
  string option = load_game.display();

  string filename = load_game.get_file_name(option);

  if (!filename.empty())
  {
    SerializationReturnCode src = Serialization::load(filename);

    if (src == SerializationReturnCode::SERIALIZATION_OK)
    {
      Serialization::delete_savefile(filename);
      result = true;
    }
  }

  return result;
}

// Exit
bool ShadowOfTheWyrmEngine::process_exit_game()
{
  return true;
}