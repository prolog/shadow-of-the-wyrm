#include <future>
#include <thread>
#include "ShadowOfTheWyrmEngine.hpp"
#include "AgeSelectionScreen.hpp"
#include "Class.hpp"
#include "ClassSelectionScreen.hpp"
#include "Conversion.hpp"
#include "Creature.hpp"
#include "CreatureFactory.hpp"
#include "CreatureUtils.hpp"
#include "DeitySelectionScreen.hpp"
#include "DisplaySettings.hpp"
#include "DisplayTile.hpp"
#include "EyeSelectionScreen.hpp"
#include "FeatureGenerator.hpp"
#include "FileConstants.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HairSelectionScreen.hpp"
#include "HelpCommandProcessor.hpp"
#include "HelpScreen.hpp"
#include "HighScoreScreen.hpp"
#include "ItemDescriptionRandomizer.hpp"
#include "ItemIdentifier.hpp"
#include "LoadGameScreen.hpp"
#include "Log.hpp"
#include "MapProperties.hpp"
#include "MessageManagerFactory.hpp"
#include "NamingScreen.hpp"
#include "Naming.hpp"
#include "PlayerDecisionStrategy.hpp"
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
#include "XMLConfigurationReader.hpp"
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
                                   { "e", EngineStateEnum::ENGINE_STATE_SHOW_HELP },
                                   { "z", EngineStateEnum::ENGINE_STATE_STOP } };
}

void ShadowOfTheWyrmEngine::initialize_game_flow_map()
{
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_START_NEW_GAME, &ShadowOfTheWyrmEngine::process_new_game));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_START_NEW_GAME_RANDOM, &ShadowOfTheWyrmEngine::process_new_game_random));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_SHOW_HIGH_SCORES, &ShadowOfTheWyrmEngine::process_show_high_scores));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_LOAD_GAME, &ShadowOfTheWyrmEngine::process_load_game));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_SHOW_HELP, &ShadowOfTheWyrmEngine::process_show_help));
  game_flow_functions.insert(make_pair(EngineStateEnum::ENGINE_STATE_STOP, &ShadowOfTheWyrmEngine::process_exit_game));
}

string ShadowOfTheWyrmEngine::start(const Settings& settings)
{
  string msg;
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
      auto d_details = display->create();
      disp_ok = d_details.first;

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
        msg = d_details.second;
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

  return msg;
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

    // For graphical/tiled displays, force ASCII?
    bool force_ascii = settings.get_setting_as_bool(Setting::DISPLAY_FORCE_ASCII);
    display->set_force_ascii(force_ascii);
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

  const DeityMap& deities = reader.get_deities();      
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
      display->display_splash(false);

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
  const Settings& settings = game.get_settings_ref();
  string default_sex = settings.get_setting(Setting::DEFAULT_SEX);
  CreatureSex sex = CreatureSex::CREATURE_SEX_NOT_SPECIFIED;

  if (default_sex != to_string(static_cast<int>(CreatureSex::CREATURE_SEX_NOT_SPECIFIED)))
  {
    sex = static_cast<CreatureSex>(RNG::range(static_cast<int>(CreatureSex::CREATURE_SEX_MALE), static_cast<int>(CreatureSex::CREATURE_SEX_FEMALE)));
  }

  // Random playable race id
  Race* race = CreatureUtils::get_random_user_playable_race();

  // Random playable class id
  Class* cur_class = CreatureUtils::get_random_user_playable_class();

  // Random allowable deity
  Deity* deity = CreatureUtils::get_random_deity_for_race(race);

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
  const Settings& settings = game.get_settings_ref();
  CreatureSex sex = CreatureSex::CREATURE_SEX_MALE;
    
  const DeityMap& deities = game.get_deities_cref();
  const RaceMap& races   = game.get_races_ref();
  const ClassMap& classes = game.get_classes_ref();
  
  Option opt;

  string default_sex = settings.get_setting(Setting::DEFAULT_SEX);
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
  auto r_it = races.find(default_race_id);
  bool prompt_user_for_race_selection = true;
  string selected_race_id;
  Race* race = nullptr;

  if (r_it != races.end())
  {
    race = r_it->second.get();

    if (race && race->get_user_playable())
    {
      prompt_user_for_race_selection = false;
      selected_race_id = default_race_id;
    }
  }

  string creature_synopsis;

  if (prompt_user_for_race_selection)
  {
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, nullptr, nullptr, nullptr, nullptr);
    RaceSelectionScreen race_selection(display, creature_synopsis);
    string race_index = race_selection.display();

    if (opt.is_random_option(race_index.at(0)))
    {
      Race* random_race = CreatureUtils::get_random_user_playable_race();

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

  string default_class_id = settings.get_setting(Setting::DEFAULT_CLASS_ID);
  const auto c_it = classes.find(default_class_id);
  bool prompt_user_for_class_selection = true;
  string selected_class_id;

  if (c_it != classes.end())
  {
    Class* cur_class = c_it->second.get();

    if (cur_class && cur_class->get_user_playable())
    {
      prompt_user_for_class_selection = false;
      selected_class_id = default_class_id;
    }
  }

  if (prompt_user_for_class_selection)
  {
    RaceManager rm;
    Race* sel_race = rm.get_race(selected_race_id);
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, sel_race, nullptr, nullptr, nullptr);
    
    ClassSelectionScreen class_selection(display, creature_synopsis);
    string class_index = class_selection.display();

    if (opt.is_random_option(class_index.at(0)))
    {
      Class* cur_class = CreatureUtils::get_random_user_playable_class();

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

  Race* selected_race = races.find(selected_race_id)->second.get();
  Class* selected_class = classes.find(selected_class_id)->second.get();

  creature_synopsis = TextMessages::get_character_creation_synopsis(sex, selected_race, selected_class, nullptr, nullptr);

  HairColour hair_colour = HairColour::HAIR_NA;
  string default_hair = settings.get_setting(Setting::DEFAULT_HAIR_COLOUR);

  if (!default_hair.empty())
  {
    HairColour hc = static_cast<HairColour>(String::to_int(default_hair));

    if (hc == HairColour::HAIR_NA)
    {
      HairSelectionScreen hss(display, creature_synopsis);
      string val = hss.display();

      if (!opt.is_random_option(val.at(0)))
      {
        hair_colour = static_cast<HairColour>(Char::keyboard_selection_char_to_int(val.at(0)));
      }
    }
    else
    {
      hair_colour = hc;
    }
  }

  EyeColour eye_colour = EyeColour::EYE_COLOUR_NA;
  string default_eye = settings.get_setting(Setting::DEFAULT_EYE_COLOUR);
  if (!default_eye.empty())
  {
    EyeColour ec = static_cast<EyeColour>(String::to_int(default_eye));

    if (ec == EyeColour::EYE_COLOUR_NA)
    {
      EyeSelectionScreen ess(display, creature_synopsis);
      string val = ess.display();

      if (!opt.is_random_option(val.at(0)))
      {
        eye_colour = static_cast<EyeColour>(Char::keyboard_selection_char_to_int(val.at(0)));
      }
    }
    else
    {
      eye_colour = ec;
    }
  }

  string default_age = settings.get_setting(Setting::DEFAULT_AGE);
  bool show_age_screen = false;
  int age = -1;

  if (race != nullptr)
  {
    if (!default_age.empty())
    {
      age = String::to_int(default_age);

      if (age == -1)
      {
        show_age_screen = true;
      }
    }
  }

  if (show_age_screen)
  {
    RaceManager rm;
    Race* sel_race = rm.get_race(selected_race_id);
    AgeInfo age_info = sel_race->get_age_info();
    int min_select_age = age_info.get_starting_age().get_min();
    int max_select_age = age_info.get_maximum_age().get_min() - 1;
    bool valid_age = false;

    while (!valid_age)
    {
      AgeSelectionScreen ass(display, creature_synopsis, min_select_age, max_select_age);
      age = String::to_int(ass.display());
      valid_age = selected_race->is_valid_starting_age(age);
    }
  }

  string default_deity_id = settings.get_setting(Setting::DEFAULT_DEITY_ID);
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
    DeitySelectionScreen deity_selection(display, selected_race, creature_synopsis);
    string deity_index = deity_selection.display();

    if (opt.is_random_option(deity_index.at(0)))
    {
      Deity* deity = CreatureUtils::get_random_deity_for_race(selected_race);

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

  Deity* selected_deity = nullptr;
  auto d_it = deities.find(selected_deity_id);
  if (d_it != deities.end())
  {
    selected_deity = d_it->second.get();
  }

  string default_starting_location_id = settings.get_setting(Setting::DEFAULT_STARTING_LOCATION_ID);
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
    creature_synopsis = TextMessages::get_character_creation_synopsis(sex, selected_race, selected_class, selected_deity, nullptr);
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

  CharacterCreationDetails ccd(sex, hair_colour, eye_colour, age, selected_race_id, selected_class_id, selected_deity_id, sl);
  return process_name_and_start(ccd);
}

bool ShadowOfTheWyrmEngine::process_name_and_start(const CharacterCreationDetails& ccd)
{
  Game& game = Game::instance();

  const RaceMap& races = game.get_races_ref();
  const ClassMap& classes = game.get_classes_ref();
  const DeityMap& deities = game.get_deities_cref();

  Race* selected_race = races.at(ccd.get_race_id()).get();
  Class* selected_class = classes.at(ccd.get_class_id()).get();
  Deity* deity = deities.at(ccd.get_deity_id()).get();
  string name;

  bool user_and_character_exist = true;
  StartingLocation sl = ccd.get_starting_location();
  string creature_synopsis = TextMessages::get_character_creation_synopsis(ccd.get_sex(), selected_race, selected_class, deity, &sl);
  string default_name = game.get_settings_ref().get_setting(Setting::DEFAULT_NAME);
  bool username_is_character_name = String::to_bool(game.get_settings_ref().get_setting(Setting::USERNAME_IS_CHARACTER_NAME));
  string warning_message;

  while (user_and_character_exist)
  {
    if (username_is_character_name && !warning_message.empty())
    {
      name = Environment::get_user_name();
    }
    else
    {
      if (default_name.empty() || !warning_message.empty())
      {
        NamingScreen naming(display, creature_synopsis, warning_message);
        name = naming.display();
      }
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
  CreaturePtr player = cf.create_by_race_and_class(game.get_action_manager_ref(), nullptr, ccd.get_race_id(), ccd.get_class_id(), name, ccd.get_sex(), CreatureSize::CREATURE_SIZE_NA, ccd.get_deity_id(), true, true);

  if (selected_race != nullptr && selected_race->is_valid_starting_age(ccd.get_age()))
  {
    player->set_age(ccd.get_age());
  }

  HairColour hc = ccd.get_hair_colour();
  EyeColour ec = ccd.get_eye_colour();

  if (hc != HairColour::HAIR_NA)
  {
    player->set_hair_colour(hc);
  }

  if (ec != EyeColour::EYE_COLOUR_NA)
  {
    player->set_eye_colour(ec);
  }

  cf.setup_player(player, controller);

  setup_auto_action_settings(player);

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

  {
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
      game.get_current_map()->reset_creatures_and_creature_locations();
    }

    // JCD TODO: Add support for additional reloadable settings here.
    // E.g., autopickup
    Settings user_settings(true, true);
    Settings kb_settings(true, false);

    kb_settings.merge_user_settings(user_settings);

    map<string, string> keybinding_settings = kb_settings.get_keybindings();

    game.get_settings_ref().set_settings(keybinding_settings);
  }

  game.set_requires_redraw(true);
  return result;
}

bool ShadowOfTheWyrmEngine::process_show_help()
{
  Game& game = Game::instance();
  CreaturePtr c = std::make_shared<Creature>();
  DecisionStrategyPtr pdstrat = std::make_unique<PlayerDecisionStrategy>(controller);
  c->set_decision_strategy(std::move(pdstrat));

  game.get_action_manager_ref().help(c);

  return false;
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

void ShadowOfTheWyrmEngine::setup_auto_action_settings(CreaturePtr player)
{
  if (player != nullptr)
  {
    Game& game = Game::instance();
    Settings& settings = game.get_settings_ref();
    bool autopickup = settings.get_setting_as_bool(Setting::AUTOPICKUP);
    bool automelee = settings.get_setting_as_bool(Setting::AUTOMELEE);
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

    DecisionStrategy* dec = player->get_decision_strategy();
    if (dec != nullptr)
    {
      dec->set_autopickup(autopickup);
      dec->set_autopickup_types(itypes);
      dec->set_automelee(automelee);
    }
  }
}
