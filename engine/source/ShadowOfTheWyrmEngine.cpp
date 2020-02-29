#include <future>
#include <thread>
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
#include "FeatureGenerator.hpp"
#include "FileConstants.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HighScoreScreen.hpp"
#include "ItemDescriptionRandomizer.hpp"
#include "ItemIdentifier.hpp"
#include "LoadGameScreen.hpp"
#include "Log.hpp"
#include "MapProperties.hpp"
#include "MessageManagerFactory.hpp"
#include "NamingScreen.hpp"
#include "Naming.hpp"
#include "RaceManager.hpp"
#include "RaceSelectionScreen.hpp"
#include "RNG.hpp"
#include "ScriptConstants.hpp"
#include "Serialization.hpp"
#include "Settings.hpp"
#include "Setting.hpp"
#include "SexSelectionScreen.hpp"
#include "StartingLocationSelectionScreen.hpp"
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

bool EngineStateManager::show_high_scores() const
{
  return (current_state == EngineStateEnum::ENGINE_STATE_SHOW_HIGH_SCORES);
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
                                   { "d", EngineStateEnum::ENGINE_STATE_SHOW_HIGH_SCORES },
                                   { "z", EngineStateEnum::ENGINE_STATE_STOP } };
}

void ShadowOfTheWyrmEngine::initialize_game_flow_map()
{
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_START_NEW_GAME, &ShadowOfTheWyrmEngine::process_new_game));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_START_NEW_GAME_RANDOM, &ShadowOfTheWyrmEngine::process_new_game_random));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_SHOW_HIGH_SCORES, &ShadowOfTheWyrmEngine::process_show_high_scores));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_LOAD_GAME, &ShadowOfTheWyrmEngine::process_load_game));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_STOP, &ShadowOfTheWyrmEngine::process_exit_game));
}

void ShadowOfTheWyrmEngine::start(const Settings& settings)
{
  Game& game = Game::instance();
  Log& log = Log::instance();

  game.set_settings(settings);
  game.actions.reload_scripts_textures_and_sids();
  bool disp_ok = true;

  if (state_manager.start_new_game())
  {
    log.debug("Setting up display.");
    setup_display(settings);

    // Read in all the game data (there's a lot of it!), and then show the
    // display
    log.debug("Reading game data.");
    setup_game();

    DisplayPtr display = game.get_display();

    if (display)
    {
      disp_ok = display->create();

      if (disp_ok)
      {
        display->set_spritesheets(game.get_spritesheets());
        display->set_title(StringTable::get(TextKeys::SW_TITLE));
        display->show();
      }
      else
      {
        // If we couldn't create the display, set the appropriate engine
        // state so we don't try to continue.
        state_manager.set_state(EngineStateEnum::ENGINE_STATE_STOP);
      }
    }
  }

  if (disp_ok)
  { 
    setup_player_and_world();

    if (!state_manager.exit())
    {
      game.go();
    }
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

    string mono_colour = DisplaySettings::DISPLAY_SETTING_MONOCHROME_COLOUR;
    display->set_property(mono_colour, settings.get_setting(mono_colour));
  }
}

// Set up everything needed by the Game
void ShadowOfTheWyrmEngine::setup_game()
{
  Game& game = Game::instance();
  Log& log = Log::instance();

  string config_file = game.get_settings_ref().get_setting(Setting::CONFIGURATION_FILE_BASE);
  string config_file_creatures = game.get_settings_ref().get_setting(Setting::CONFIGURATION_FILE_CREATURES);
  string config_file_items = game.get_settings_ref().get_setting(Setting::CONFIGURATION_FILE_ITEMS);

  XMLConfigurationReader reader(config_file, config_file_creatures, config_file_items);

  log.debug("Reading spritesheets.");

  // Set the spritesheets so they can be set into the display later if 
  // we're using SDL.
  game.set_spritesheets(reader.get_spritesheets());

  // Read the races, classes, and items from the configuration file.
  // Items need to be read first so that each class's default items can be loaded.
  // Custom maps are read last because they rely on creatures (which rely on races
  // and classes), and items.
  game.set_display(display);

  log.debug("Reading items.");

  pair<ItemMap, GenerationValuesMap> items = reader.get_items();
  game.set_items(items.first);
  game.set_item_generation_values(items.second);

  log.debug("Reading feature symbols.");

  FeatureSymbolMap feature_symbols = reader.get_feature_symbols();
  FeatureGenerator::set_feature_symbol_map(feature_symbols);

  log.debug("Reading configurable features.");

  FeatureMap configurable_features = reader.get_configurable_features();
  game.set_configurable_features(configurable_features);

  log.debug("Randomizing certain item types.");

  // Randomize the items after reading them!  Otherwise, if any potions, etc.,
  // are generated e.g. during custom map initialization, they will always have
  // the same descriptions.
  vector<ItemType> item_types{ ItemType::ITEM_TYPE_SCROLL, ItemType::ITEM_TYPE_WAND, ItemType::ITEM_TYPE_STAFF, ItemType::ITEM_TYPE_SPELLBOOK, ItemType::ITEM_TYPE_RING, ItemType::ITEM_TYPE_POTION, ItemType::ITEM_TYPE_AMULET };
  ItemDescriptionRandomizer item_randomizer(item_types);
  item_randomizer.randomize(game.items);

  log.debug("Reading scripts.");

  map<string, string> scripts = reader.get_scripts();
  game.set_scripts(scripts);

  log.debug("Reading deities.");

  DeityMap deities = reader.get_deities();      
  game.set_deities(deities);

  log.debug("Reading races.");

  RaceMap races = reader.get_races();
  game.set_races(races);

  log.debug("Reading classes.");

  ClassMap classes = reader.get_classes();
  game.set_classes(classes);

  log.debug("Reading creatures.");

  pair<CreatureMap, CreatureGenerationValuesMap> creatures = reader.get_creatures();    
  game.set_creatures(creatures.first);
  game.set_creature_generation_values(creatures.second);

  log.debug("Reading spells.");

  SpellMap spells = reader.get_spells();
  game.set_spells(spells);

  log.debug("Reading tile info.");

  vector<DisplayTile> tile_info = reader.get_tile_info();
  game.set_tile_display_info(tile_info);

  log.debug("Reading trap info.");
  
  vector<TrapPtr> trap_info = reader.get_trap_info();
  game.set_trap_info(trap_info);

  log.debug("Reading calendar days.");

  map<int, CalendarDay> calendar_days = reader.get_calendar_days();
  game.set_calendar_days(calendar_days);

  log.debug("Reading starting locations.");

  StartingLocationMap starting_locations = reader.get_starting_locations();
  game.set_starting_locations(starting_locations);

  log.debug("Reading custom maps.");

  // This switches files/namespaces - so should be last.
  // As part of setting the custom maps, the game may run any associated
  // scripts.
  vector<MapPtr> custom_maps = reader.get_custom_maps(FileConstants::CUSTOM_MAPS_DIRECTORY, FileConstants::CUSTOM_MAPS_PATTERN);
  game.set_custom_maps(custom_maps);

  log.debug("Setting message manager display.");

  // Set up the message manager also.
  IMessageManager& manager = MM::instance();
  manager.set_display(display);

  log.debug("Done setup.");
}

// Create the player
void ShadowOfTheWyrmEngine::setup_player_and_world()
{
  bool done = false;

  while (!done)
  {
    string game_option;

    {
      WelcomeScreen welcome(display);
      game_option = welcome.display();
    }

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
  if (!is_new_game_allowed())
  {
    // Add an alert for the user.
    return false;
  }

  CharacterCreationDetails ccd;

  // Random sex
  Game& game = Game::instance();
  string default_sex = game.get_settings_ref().get_setting(Setting::DEFAULT_SEX);
  CreatureSex sex = CreatureSex::CREATURE_SEX_NOT_SPECIFIED;

  if (default_sex != to_string(static_cast<int>(CreatureSex::CREATURE_SEX_NOT_SPECIFIED)))
  {
    sex = static_cast<CreatureSex>(RNG::range(static_cast<int>(CreatureSex::CREATURE_SEX_MALE), static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE)));
  }

  // Random playable race id
  RacePtr race = CreatureUtils::get_random_user_playable_race();

  // Random playable class id
  ClassPtr cur_class = CreatureUtils::get_random_user_playable_class();

  // Random allowable deity
  DeityPtr deity = CreatureUtils::get_random_deity_for_race(race);

  // Random starting location
  StartingLocationMap sm = Game::instance().get_starting_locations();
  StartingLocation sl = GameUtils::get_random_starting_location(sm);

  if (race && cur_class && deity)
  {
    ccd.set_sex(sex);
    ccd.set_race_id(race->get_race_id());
    ccd.set_class_id(cur_class->get_class_id());
    ccd.set_deity_id(deity->get_id());
    ccd.set_starting_location(sl);
  }

  // Get name, and start.
  return process_name_and_start(ccd);
}

// Process a new game command
bool ShadowOfTheWyrmEngine::process_new_game()
{
  if (!is_new_game_allowed())
  {
    // Add an alert for the user.
    return false;
  }

  Game& game = Game::instance();
  CreatureSex sex = CreatureSex::CREATURE_SEX_MALE;
    
  DeityMap deities = game.get_deities_cref();
  RaceMap  races   = game.get_races_ref();
  ClassMap classes = game.get_classes_ref();
  
  Option opt;

  string default_sex = game.get_settings_ref().get_setting(Setting::DEFAULT_SEX);
  bool prompt_user_for_sex = true;

  if (!default_sex.empty())
  {
    int sex_i = String::to_int(default_sex);
    sex = static_cast<CreatureSex>(sex_i);
    prompt_user_for_sex = false;
  }

  if (prompt_user_for_sex)
  {
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
  }

  string default_race_id = game.get_settings_ref().get_setting(Setting::DEFAULT_RACE_ID);
  const auto r_it = races.find(default_race_id);
  bool prompt_user_for_race_selection = true;
  string selected_race_id;

  if (r_it != races.end())
  {
    RacePtr race = r_it->second;

    if (race && race->get_user_playable())
    {
      prompt_user_for_race_selection = false;
      selected_race_id = default_race_id;
    }
  }

  string creature_synopsis;

  if (prompt_user_for_race_selection)
  {
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, nullptr, nullptr, nullptr);
    RaceSelectionScreen race_selection(display, creature_synopsis);
    string race_index = race_selection.display();

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
  }

  string default_class_id = game.get_settings_ref().get_setting(Setting::DEFAULT_CLASS_ID);
  const auto c_it = classes.find(default_class_id);
  bool prompt_user_for_class_selection = true;
  string selected_class_id;

  if (c_it != classes.end())
  {
    ClassPtr cur_class = c_it->second;

    if (cur_class && cur_class->get_user_playable())
    {
      prompt_user_for_class_selection = false;
      selected_class_id = default_class_id;
    }
  }

  if (prompt_user_for_class_selection)
  {
    RaceManager rm;
    RacePtr sel_race = rm.get_race(selected_race_id);
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, sel_race, nullptr, nullptr);
    
    ClassSelectionScreen class_selection(display, creature_synopsis);
    string class_index = class_selection.display();

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
  }

  RacePtr selected_race = races[selected_race_id];
  ClassPtr selected_class = classes[selected_class_id];

  string default_deity_id = game.get_settings_ref().get_setting(Setting::DEFAULT_DEITY_ID);
  bool prompt_user_for_deity_selection = true;
  vector<string> deity_ids = selected_race->get_initial_deity_ids();
  string selected_deity_id;

  if (std::find(deity_ids.begin(), deity_ids.end(), default_deity_id) != deity_ids.end())
  {
    selected_deity_id = default_deity_id;
    prompt_user_for_deity_selection = false;
  }

  if (prompt_user_for_deity_selection)
  {
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, selected_race, selected_class, nullptr);

    DeitySelectionScreen deity_selection(display, selected_race, creature_synopsis);
    string deity_index = deity_selection.display();

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
  }

  DeityPtr selected_deity = deities[selected_deity_id];
  string default_starting_location_id = game.get_settings_ref().get_setting(Setting::DEFAULT_STARTING_LOCATION_ID);
  StartingLocationMap sm = game.get_starting_locations();
  StartingLocation sl;
  auto sm_it = sm.find(default_starting_location_id);

  if (sm_it != sm.end())
  {
    sl = sm_it->second;
  }
  else
  {
    string deity_sid = selected_deity->get_name_sid();    
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, selected_race, selected_class, selected_deity);
    StartingLocationSelectionScreen sl_selection(display, creature_synopsis, sm);
    string sl_sidx = sl_selection.display();

    if (opt.is_random_option(sl_sidx.at(0)))
    {
      sl = GameUtils::get_random_starting_location(sm);
    }
    else
    {
      int sl_idx = Char::keyboard_selection_char_to_int(sl_sidx.at(0));
      string selected_starting_location_id = Integer::to_string_key_at_given_position_in_map(sm, sl_idx);
      sl = sm.find(selected_starting_location_id)->second;
    }
  }

  CharacterCreationDetails ccd(sex, selected_race_id, selected_class_id, selected_deity_id, sl);
  return process_name_and_start(ccd);
}

bool ShadowOfTheWyrmEngine::process_name_and_start(const CharacterCreationDetails& ccd)
{
  Game& game = Game::instance();

  RaceMap  races = game.get_races_ref();
  ClassMap classes = game.get_classes_ref();
  DeityMap deities = game.get_deities_cref();

  RacePtr selected_race = races.at(ccd.get_race_id());
  ClassPtr selected_class = classes.at(ccd.get_class_id());
  DeityPtr deity = deities.at(ccd.get_deity_id());
  string name;

  bool user_and_character_exist = true;
  string creature_synopsis = TextMessages::get_character_creation_synopsis(ccd.get_sex(), selected_race, selected_class, deity);
  string warning_message;

  while (user_and_character_exist)
  {
    Settings& settings = game.get_settings_ref();
    string default_name = settings.get_setting(Setting::DEFAULT_NAME);
    bool username_is_character_name = String::to_bool(settings.get_setting(Setting::USERNAME_IS_CHARACTER_NAME));
    
    if (username_is_character_name)
    {
      name = Environment::get_user_name();
    }
    else
    {
      NamingScreen naming(display, creature_synopsis, warning_message);
      name = naming.display();
    }

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
  cf.setup_player(player, controller);

  setup_autopickup_settings(player);

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

  game.create_new_world(player, ccd.get_starting_location());

  // Run the "special day" script.
  game.get_script_engine_ref().execute(game.get_script(ScriptConstants::SPECIAL_DAY_SCRIPT), {});

  return true;
}

bool ShadowOfTheWyrmEngine::process_show_high_scores()
{
  Game& game = Game::instance();
  ScoreFile sf;

  HighScoreScreen hss(game.get_display(), sf.get_entries());
  hss.display();

  return false;
}

// Process a load game command. Load the game and then reload the keybindings
// from disk, as the saved game will have settings based on when the savefile
// was originally created.
bool ShadowOfTheWyrmEngine::process_load_game()
{
  bool result = false;
  Game& game = Game::instance();

  LoadGameScreen load_game(display);
  string option = load_game.display();

  string filename = load_game.get_file_name(option);

  if (!filename.empty())
  {
    // Do the load asynchronously or SDL/Windows can flip out because of
    // events not being responded to.
    promise<SerializationReturnCode> sp;
    future<SerializationReturnCode> sf = sp.get_future();
    DisplayPtr cur_display = display;
    ControllerPtr cur_controller = controller;

    std::thread thread([&]() {
      SerializationReturnCode src = Serialization::load(filename);
      
      game.set_display(cur_display);
      CreaturePtr player = game.get_current_player();
        
      if (player != nullptr)
      {
        player->get_decision_strategy()->set_controller(cur_controller);
      } 

      sp.set_value(src);
    });

    game.set_loading();

    while (sf.wait_for(std::chrono::milliseconds(250)) != std::future_status::ready)
    {
      controller->poll_event();
    }

    thread.join();
    SerializationReturnCode src = sf.get();

    if (src == SerializationReturnCode::SERIALIZATION_OK)
    {
      game.set_current_loaded_savefile(filename);
      result = true;
    }

    game.set_ready();
  }

  // JCD TODO: Add support for additional reloadable settings here.
  // E.g., autopickup
  Settings kb_settings(true);
  map<string, string> keybinding_settings = kb_settings.get_keybindings();

  game.get_settings_ref().set_settings(keybinding_settings);

  return result;
}

// Exit
bool ShadowOfTheWyrmEngine::process_exit_game()
{
  return true;
}

// Check to see if a new game is allowed.
// In practical terms, check to see if the user has hit the maximum number
// of characters that can be created per user.
bool ShadowOfTheWyrmEngine::is_new_game_allowed()
{
  bool allowed = true;
  IMessageManager& manager = MM::instance();
  Game& game = Game::instance();
  Settings& settings = game.get_settings_ref();
  string max_chars = settings.get_setting(Setting::MAX_CHARACTERS_PER_USER);
  bool username_is_character_name = String::to_bool(settings.get_setting(Setting::USERNAME_IS_CHARACTER_NAME));
  bool single_user_mode = settings.get_setting_as_bool(Setting::SINGLE_USER_MODE);
  bool skip_savefile_verification = settings.get_setting_as_bool(Setting::SKIP_SAVEFILE_METADATA_VERIFICATION);
  int num_allowed = -1;

  if (!max_chars.empty())
  {
    num_allowed = String::to_int(max_chars);
  }

  if (username_is_character_name)
  {
    num_allowed = 1;
  }

  if (num_allowed > -1)
  {
    // Get a list of savefiles for the user, and then see if the limit's been
    // reached, adding an alert if it has.
    vector<pair<string, string>> savefile_details = Serialization::get_save_file_names(single_user_mode, skip_savefile_verification);
    size_t num_savefiles = savefile_details.size();

    if (num_savefiles >= static_cast<size_t>(num_allowed) || (num_savefiles > 0 && username_is_character_name))
    {
      manager.alert(StringTable::get(TextKeys::NO_NEW_CHARACTERS));
      allowed = false;
    }
  }

  return allowed;
}

void ShadowOfTheWyrmEngine::setup_autopickup_settings(CreaturePtr player)
{
  if (player != nullptr)
  {
    Game& game = Game::instance();
    Settings& settings = game.get_settings_ref();
    bool autopickup = settings.get_setting_as_bool(Setting::AUTOPICKUP);
    vector<string> auto_types_s = String::create_string_vector_from_csv_string(settings.get_setting(Setting::AUTOPICKUP_TYPES));
    set<ItemType> itypes;

    for (const auto& it_s : auto_types_s)
    {
      if (!it_s.empty())
      {
        ItemType it = static_cast<ItemType>(String::to_int(it_s));
        itypes.insert(it);
      }
    }

    DecisionStrategyPtr dec = player->get_decision_strategy();
    if (dec != nullptr)
    {
      dec->set_autopickup(autopickup);
      dec->set_autopickup_types(itypes);
    }
  }
}
