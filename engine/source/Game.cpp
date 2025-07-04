#ifdef _MSC_VER
#pragma warning(disable : 4996)
#endif
#include <chrono>
#include <ctime>
#include <future>
#include <boost/timer/timer.hpp>
#include "global_prototypes.hpp"
#include "AmbientSound.hpp"
#include "CommandProcessor.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureTranslator.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureCoordinateCalculator.hpp"
#include "CreatureFeatures.hpp"
#include "CreatureGenerationIndex.hpp"
#include "CreatureProperties.hpp"
#include "CreatureUtils.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "CustomAreaGenerator.hpp"
#include "CursesConstants.hpp"
#include "DecisionStrategySelector.hpp"
#include "DetectionSkillProcessor.hpp"
#include "DisplaySettings.hpp"
#include "DisplayStatistics.hpp"
#include "EngineConversion.hpp"
#include "ExitGameAction.hpp"
#include "FeatureGenerator.hpp"
#include "FileConstants.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "HighScoreScreen.hpp"
#include "ItemSerializationFactory.hpp"
#include "LineOfSightCalculator.hpp"
#include "Log.hpp"
#include "MapCursor.hpp"
#include "MapScript.hpp"
#include "MapUtils.hpp"
#include "MapTranslator.hpp"
#include "MessageManagerFactory.hpp"
#include "RNG.hpp"
#include "ScoreFile.hpp"
#include "ScoreTextKeys.hpp"
#include "Serialize.hpp"
#include "Serialization.hpp"
#include "Setting.hpp"
#include "SkillProcessors.hpp"
#include "SoundFactory.hpp"
#include "StatusActionProcessor.hpp"
#include "StealthSkillProcessor.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "ViewMapTranslator.hpp"
#include "WorldGenerator.hpp"
#include "WorldMapLocationTextKeys.hpp"
#include "WorldTimeKeeperCoordinator.hpp"

// Used by serialization code:
#include "CommandFactoryFactory.hpp"
#include "DisplayFactory.hpp"
#include "KeyboardCommandMapFactory.hpp"

using namespace std;

Game::Game()
: keep_playing(true)
, reload_game_loop(false)
, check_scores(true)
, requires_redraw(true)
, count_score(true)
, total_seconds_played(0.0)
, game_start_time(chrono::system_clock::now())
, is_loading(false)
{
  // Setup the time keeper.  On a new game, this will initialize everything as
  // expected - when loading an existing game, this will be overwritten later,
  // which is fine.
  WorldTimeKeeperCoordinator time_coordinator;
  time_coordinator.setup_time_keeper(time_keeper);
}

Game::~Game()
{
}

void Game::set_title_text(const string& new_title_text)
{
  if (display != nullptr)
  {
    display->set_title(StringTable::get(new_title_text));
  }
}
void Game::set_loading()
{
  set_title_text(TextKeys::SW_TITLE_LOADING);
  is_loading = true;
}

void Game::set_ready()
{
  if (display != nullptr)
  {
    display->set_title(StringTable::get(TextKeys::SW_TITLE));
  }

  is_loading = false;
}

bool Game::get_loading() const
{
  return is_loading;
}

void Game::set_requires_redraw(const bool new_requires_redraw)
{
  requires_redraw = new_requires_redraw;
}

bool Game::get_requires_redraw() const
{
  return requires_redraw;
}

// Set the settings, and also update any other settings (like the language
// file, etc) that are derived from the settings.
void Game::set_settings(const Settings& new_settings)
{
  settings = new_settings;

  string language_file = settings.get_setting(Setting::LANGUAGE_FILE);
  set_sid_ini_filename(language_file);

  string log_level = settings.get_setting(Setting::LOG_LEVEL);
  LoggingLevel ll = static_cast<LoggingLevel>(String::to_int(log_level));

  if (ll >= LoggingLevel::LOG_LOWEST && ll < LoggingLevel::LOG_HIGHEST)
  {
    Log::instance().set_log_level(ll);
  }

  set_display_settings();
  set_world_settings();
}

void Game::set_display_settings()
{
  string cursor_mode = settings.get_setting(Setting::CURSOR_MODE);
  CursorMode cm = static_cast<CursorMode>(String::to_int(cursor_mode));

  // Game may just be starting up.
  if (display != nullptr)
  {
    if (cm >= CursorMode::CURSOR_MODE_MIN && cm <= CursorMode::CURSOR_MODE_MAX)
    {
      DisplayPtr disp = get_display();
      disp->set_property(DisplaySettings::DISPLAY_SETTING_CURSOR_MODE, cursor_mode);
    }
  }
}

void Game::set_world_settings()
{
  uint days_elapsed = String::to_uint(settings.get_setting(Setting::DAYS_ELAPSED));
  uint hours_elapsed = String::to_uint(settings.get_setting(Setting::HOURS_ELAPSED));
  bool current_month_is_start_month = String::to_bool(settings.get_setting(Setting::CURRENT_MONTH_IS_START_MONTH));

  if (current_month_is_start_month)
  {    
    std::time_t now_c = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    struct tm *parts = std::localtime(&now_c);

    days_elapsed = (parts->tm_mon * 30);
  }

  World* wrld = get_current_world();

  // If we're just starting up, the world may not have been instantiated yet.
  if (wrld != nullptr)
  {
    wrld->get_calendar().set_date(days_elapsed, hours_elapsed);
  }
}

Settings& Game::get_settings_ref()
{
  return settings;
}

void Game::set_display(DisplayPtr game_display)
{
  display = game_display;
  set_display_settings();
}

DisplayPtr Game::get_display() const
{
  return display;
}

void Game::set_sound(SoundPtr game_sound)
{
  sound = game_sound;
}

SoundPtr Game::get_sound() const
{
  return sound;
}

// Returns the real sound pointer if the creature is null or the player (if 
// the sound should always be played), or else a NullSound pointer, which
// suppresses the sound effect.
SoundPtr Game::get_sound(CreaturePtr creature)
{
  if (creature == nullptr || creature->get_is_player())
  {
    return sound;
  }
  else
  {
    SoundFactory sf;
    SoundPtr snd = sf.create_null_sound();

    return snd;
  }
}

void Game::set_sound_effects(const map<pair<string, string>, string>& new_sound_effects)
{
  sound_effects = new_sound_effects;
}

const map<pair<string, string>, string>& Game::get_sound_effects_cref() const
{
  return sound_effects;
}

void Game::set_music(const Music& new_music)
{
  music = new_music;
}

Music Game::get_music() const
{
  return music;
}

const Music& Game::get_music_cref() const
{
  return music;
}

void Game::set_map_registry(const MapRegistry& new_map_registry)
{
  map_registry = new_map_registry;
}

MapRegistry& Game::get_map_registry_ref()
{
  return map_registry;
}

void Game::set_deities(const DeityMap& game_deities)
{
  deities.clear();

  for (const auto& gd_it : game_deities)
  {
    DeityPtr deity = std::make_unique<Deity>(*gd_it.second);
    deities.insert(make_pair(gd_it.first, std::move(deity)));
  }
}

DeityMap& Game::get_deities_ref()
{
  return deities;
}

bool Game::do_deities_exist() const
{
  return (deities.empty() == false);
}

const DeityMap& Game::get_deities_cref() const
{
  return deities;
}

void Game::set_races(const RaceMap& game_races)
{
  races.clear();

  for (const auto& r_it : game_races)
  {
    RacePtr race = std::make_unique<Race>(*r_it.second);
    races.insert(make_pair(r_it.first, std::move(race)));
  }
}

const RaceMap& Game::get_races_ref() const
{
  return races;
}

void Game::set_classes(const ClassMap& game_classes)
{
  classes.clear();

  for (const auto& cl_it : game_classes)
  {
    ClassPtr cur_class = std::make_unique<Class>(*cl_it.second);
    classes.insert(make_pair(cl_it.first, std::move(cur_class)));
  }
}

const ClassMap& Game::get_classes_ref() const
{
  return classes;
}

void Game::set_creatures(const CreatureMap& game_creatures)
{
  creatures = game_creatures;
}

void Game::set_spells(const SpellMap& game_spells)
{
  spells = game_spells;
}

const SpellMap& Game::get_spells_ref()
{
  return spells;
}

const CreatureMap& Game::get_creatures_ref() const
{
  return creatures;
}

void Game::set_creature_generation_values(const CreatureGenerationValuesMap& game_cgv)
{
  creature_generation_values = game_cgv;
}

CreatureGenerationValuesMap& Game::get_creature_generation_values_ref()
{
  return creature_generation_values;
}

void Game::set_item_generation_values(const GenerationValuesMap& game_igv)
{
  item_generation_values = game_igv;
}

GenerationValuesMap& Game::get_item_generation_values_ref()
{
  return item_generation_values;
}

void Game::set_items(const ItemMap& game_items)
{
  items = game_items;
}

const ItemMap& Game::get_items_ref() const
{
  return items;
}

void Game::set_configurable_features(const FeatureMap& game_features)
{
  configurable_features = game_features;
}

const FeatureMap& Game::get_configurable_features_ref() const
{
  return configurable_features;
}

void Game::set_custom_maps(const vector<MapPtr>& custom_maps)
{
  map_registry.clear_maps();

  for (MapPtr custom_map : custom_maps)
  {
    string id = custom_map->get_map_id();
    map_registry.set_map(id, custom_map);
  }

  run_map_scripts();
}

void Game::set_tile_display_info(const vector<DisplayTile>& game_tiles)
{
  tile_info = game_tiles;
}

const vector<DisplayTile>& Game::get_tile_display_info_ref() const
{
  return tile_info;
}

void Game::set_trap_info(const vector<TrapPtr>& game_traps)
{
  trap_info = game_traps;
}

const vector<TrapPtr>& Game::get_trap_info_ref() const
{
  return trap_info;
}

void Game::set_calendar_days(const map<int, CalendarDay>& new_calendar_days)
{
  calendar_days = new_calendar_days;
}

map<int, CalendarDay>& Game::get_calendar_days_ref()
{
  return calendar_days;
}

void Game::set_starting_locations(const StartingLocationMap& new_starting_locations)
{
  starting_locations = new_starting_locations;
}

StartingLocationMap Game::get_starting_locations() const
{
  return starting_locations;
}

CreaturePtr Game::get_current_player() const
{
  MapPtr current_map = get_current_map();
  CreaturePtr current_player;

  if (current_map != nullptr)
  {
    current_player = current_map->get_creature(CreatureID::CREATURE_ID_PLAYER);
  }

  return current_player;
}

ternary Game::get_winner() const 
{
  CreaturePtr player = get_current_player();
  ternary winner = ternary::TERNARY_UNDEFINED;

  if (player != nullptr)
  {
    winner = player->get_satisfied_win_conditions().empty() ? ternary::TERNARY_FALSE : ternary::TERNARY_TRUE;
  }

  return winner;
}

// Create the new world, and set the player at the special "player's starting location" point.
// Then, read in the XML areas, and overlay that on top.
void Game::create_new_world(CreaturePtr creature, const StartingLocation& sl)
{
  MapPtr current_world;
  ControllerPtr creature_controller = creature->get_decision_strategy()->get_controller();
  promise<MapPtr> mp;
  future<MapPtr> fp = mp.get_future();
  std::thread thread(async_worldgen, std::move(mp));

  set_loading();
    
  while (fp.wait_for(std::chrono::milliseconds(250)) != std::future_status::ready)
  {
    creature_controller->poll_event();
  }

  set_ready();

  thread.join();
  current_world = fp.get();

  world = WorldPtr(new World(current_world));

  set_world_settings();

  // Need to set the world map into the registry so that it's available to 
  // any scripts called by the CustomAreaGenerator.
  set_current_map(current_world);

  string world_map_areas = settings.get_setting(Setting::CONFIGURATION_FILE_WORLD_MAP_AREAS);
  CustomAreaGenerator cag(world_map_areas);
  cag.overlay_custom_areas(current_world);
  
  WorldGenerator wg;
  wg.set_village_coordinates(current_world);
  wg.set_treasure(current_world);

  MapPtr world_map = get_map_registry_ref().get_map(MapID::MAP_ID_WORLD_MAP);
  if (world_map != nullptr)
  {
    world_map->add_or_update_location(WorldMapLocationTextKeys::STARTING_LOCATION, sl.get_location());
  }

  TilePtr tile = current_world->get_tile_at_location(WorldMapLocationTextKeys::STARTING_LOCATION);

  if (tile)
  {
    tile->set_creature(creature);

    ostringstream ss;
    Date d = get_current_world()->get_calendar().get_date();
    d.serialize(ss);

    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_CHARACTER_STARTED, ss.str());
    
    std::time_t start_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    creature->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_GAME_STARTED, std::ctime(&start_time));

    // Set the starting location.
    if (creature->get_is_player())
    {
      Coordinate c = current_world->get_location(WorldMapLocationTextKeys::STARTING_LOCATION);
      MapUtils::add_or_update_location(current_world, creature, c);
    }
  }
  else
  {
    Log::instance().log("Game::create_new_world - Couldn't get player's initial starting location!");
  }
}

// Update the display, but making some assumptions.
void Game::update_display()
{
  MapPtr cur_map = get_current_map();

  if (cur_map != nullptr)
  {
    CreaturePtr creature = cur_map->get_creature(CreatureID::CREATURE_ID_PLAYER);

    if (creature != nullptr)
    {
      MapPtr fov_map = creature->get_decision_strategy()->get_fov_map();

      // Force a hard redraw.
      update_display(creature, cur_map, fov_map, false);

      if (display)
      {
        display->redraw();
      }
    }
  }
}

// Update the display: the statistics area, and the current map.
void Game::update_display(CreaturePtr current_player, MapPtr current_map, MapPtr fov_map, const bool reloaded_game)
{
  Game& game = Game::instance();

  if (current_player && current_map)
  {
    // boost::timer::auto_cpu_timer timer;
    MapDisplayArea display_area = display->get_map_display_area();

    DisplayStatistics display_stats = CreatureTranslator::create_display_statistics(current_player, current_map);
    display->display(display_stats);

    MapCursor mc;
    pair<Coordinate, bool> reference_coords = mc.get_cursor_location(current_map);

    Coordinate display_coord = CreatureCoordinateCalculator::calculate_display_coordinate(display_area, current_map, reference_coords.first);
    loaded_map_details.update_display_coord(display_coord);
    bool redraw_needed = loaded_map_details.requires_full_map_redraw() || requires_redraw || reloaded_game;

    CurrentCreatureAbilities cca;
    CreaturePtr player = game.get_current_player();

    DisplayMap display_map = MapTranslator::create_display_map(player, !cca.can_see(player), current_map, fov_map, display_area, reference_coords.first, redraw_needed);

    CursorSettings cs = CursorSettings::CURSOR_SETTINGS_USE_DEFAULT;

    if (reference_coords.second)
    {
      cs = CursorSettings::CURSOR_SETTINGS_SHOW_CURSOR;
    }

    if (redraw_needed)
    {
      display->draw(display_map, cs);
      requires_redraw = false;
    }
    else
    {
      display->draw_update_map(display_map, cs);
    }

    // Add any new required after the full redraw.
    IMessageManager& manager = MMF::instance();
    manager.send();

    // As long as there are still player actions within the current map, and we've
    // not loaded a new map, a full redraw is not needed:
    loaded_map_details.synch();
  }
}

void Game::go()
{
  AmbientSound as;
  game_command_factory = std::make_unique<CommandFactory>();
  game_kb_command_map = std::make_unique<KeyboardCommandMap>();

  set_check_scores(true);

  StatusActionProcessor sap;
  MapPtr current_map = get_current_map();
  CreaturePtr current_player = get_current_player();
  set_game_start_time(chrono::system_clock::now());

  // Use a try-catch block so that if there is an exception thrown, we can
  // try to recover by saving.
  try
  {
    // To see if this is a new game, check the ActionCoordinator to see if there is
    // a map, yet.  If there isn't, the game hasn't been restored, so it must be a
    // new game.
    bool reloaded_game = !ac.get_current_map_id().empty();

    if (reloaded_game)
    {
      MapUtils::calculate_fov_maps_for_all_creatures(current_map);
    }

    string welcome_message = TextMessages::get_welcome_message(current_player->get_name(), !reloaded_game);

    display->clear_display();
    display->refresh_current_window();

    IMessageManager& manager = MMF::instance();
    manager.add_new_message(welcome_message);
    manager.send();

    CreatureCalculator cc;
    cc.update_calculated_values(current_player);
    string map_id = "";

    sound->play_music(current_map);

    // Main game loop.
    while (keep_playing)
    {
      detect_creatures_if_necessary(current_player, map_id);

      current_map = get_current_map();

      // After loading the (new) map, a full redraw is needed.
      map_id = current_map_id;
      loaded_map_details.update_map_id(map_id);

      map<string, CreaturePtr> map_creatures = current_map->get_creatures();

      if (!reloaded_game)
      {
        ac.reset_if_necessary(current_map->get_permanent(), current_map->get_map_id(), map_creatures);
      }

      Calendar& calendar = world->get_calendar();

      while (ac.has_actions())
      {
        // Update the list of creatures after each action; otherwise, creatures that are killed
        // might persist.
        map_creatures = current_map->get_creatures();

        CreaturePtr current_creature;
        ActionCost next_action_cost = ac.get_current_action_cost();
        string creature_id = ac.get_next_creature_id();
        map<string, CreaturePtr>::iterator c_it = map_creatures.find(creature_id);

        if (c_it != map_creatures.end())
        {
          current_creature = c_it->second;

          // Now, sanity check - is the creature still at its
          // stated location?
          if (current_creature != nullptr)
          {
            string cur_cr_id = current_creature->get_id();
            Coordinate cr_loc = current_map->get_location(current_creature->get_id());
            TilePtr cur_cr_tile = current_map->at(cr_loc);

            if (cur_cr_tile && (!cur_cr_tile->has_creature() || cur_cr_tile->get_creature()->get_id() != cur_cr_id))
            {
              Log& log = Log::instance();
              if (log.debug_enabled())
              {
                log.debug("Creature with ID " + cur_cr_id + " no longer exists at its stated map location (" + String::create_string_from_coordinate(cr_loc) + "). Removing. Creature is actually at (" + current_map->get_creature_location_debug(cur_cr_id) + ").");
              }

              current_map->remove_creature(current_creature->get_id());
              current_creature = nullptr;
            }
          }
        }

        update_player_dates();

        if (!current_creature)
        {
          // Creature's been killed - advance to the next creature in the
          // queue.
          ac.update_actions();
        }
        else // Creature's fine, process its action
        {
          // If we shouldn't keep playing (player has quit, has been killed, etc), then break out of the 
          // game loop.
          if (!keep_playing) break;

          process_elapsed_time(calendar, next_action_cost);

          // Player may have been killed by some time-related effect.
          if (!keep_playing) break;

          PassiveSkillsProcessor psp;
          psp.process_passive_skills(current_creature, current_map);

          CreatureStatusMap creature_statuses_before = current_creature->get_statuses();

          ActionCost action_cost = process_action_for_creature(current_creature, current_map, reloaded_game);
          sap.process_action(current_creature, creature_statuses_before, action_cost);

          // Remove any single turn flags, if present.
          if (current_creature != nullptr)
          {
            current_creature->remove_additional_property(CreatureProperties::CREATURE_PROPERTIES_TELEPORTED);
          }
          
          // Remove the creature's current action.  This is done after the "keep_playing"
          // check so that saving, etc., does not advance the turn.
          if (keep_playing)
          {
            ac.update_actions();
            ac.add(action_cost, current_creature->get_id());
          }

          if (current_creature->get_is_player())
          {
            // Now that we've ensured that the ActionCoordinator isn't reset,
            // and that a full window redraw has been done, we can reset the
            // reloaded_game variable so that it won't override any game logic.
            reloaded_game = false;

            // When doing things as the player, ambient sounds can also happen
            string sound_effect_id = as.get_sound_effect(current_map, current_creature->get_turns());

            if (!sound_effect_id.empty())
            {
              sound->play(sound_effect_id);
            }
          }

          if (reload_game_loop)
          {
            reload_game_loop = false;
            break;
          }
        }
      }
    }

    // We're done - clear the display so that score information (or error
    // information, it is me coding this, after all) can be shown.
    if (!should_count_score())
    {
      manager.add_new_message_with_pause(StringTable::get(TextKeys::SCORE_SUPPRESSED_LUA_NARRATIVE));
      manager.send();
      get_current_player()->get_decision_strategy()->get_confirmation();
    }

    display->clear_display();
    display->redraw();
    update_score_file_if_necessary(current_player);
  }
  catch (std::exception& e)
  {
    Log::instance().error("Exception caught in main loop!  Details: ");
    Log::instance().error(e.what());

    exit_on_exception(current_player);
  }
  catch (...)
  {
    // If there was an exception, try to recover by saving and then exiting
    // so that perhaps the player can reload the save.
    exit_on_exception(current_player);
  }

  string farewell_msg = ScoreTextKeys::get_farewell_text_message(current_player->get_name());
  std::cout << farewell_msg << endl;
}

void Game::exit_on_exception(CreaturePtr player)
{
  if (player != nullptr)
  {
    panic_save(player);
  }

  // Add a message about the crash.
  string crash_msg = StringTable::get(TextKeys::SW_PROBLEM_GAME_SAVED);
  std::cout << crash_msg << endl << endl;
}

void Game::panic_save(CreaturePtr player)
{
  auto val = actions.save(player, true);
}

void Game::set_check_scores(const bool new_check_scores)
{
  check_scores = new_check_scores;
}

bool Game::should_check_scores() const
{
  return check_scores;
}

bool Game::should_count_score() const
{
  bool calc_score = true;
  bool disallow_score_on_exploration = settings.get_setting_as_bool(Setting::DISALLOW_SCORE_ON_EXPLORATION);

  if (disallow_score_on_exploration)
  {
    bool narrative_mode = settings.get_setting_as_bool(Setting::NARRATIVE_MODE);

    if (disallow_score_on_exploration && (narrative_mode || !count_score))
    {
      calc_score = false;
    }
  }

  return calc_score;
}

// Update score files if the game is being exited but not saved
// (e.g.: creature killed, wins, etc)
void Game::update_score_file_if_necessary(CreaturePtr current_player)
{
  // Do scorefile wizardry? (is the game being exited for reasons other
  // than saving?)
  if (should_check_scores())
  {
    try
    {
      if (should_count_score())
      {
        ScoreFile sf;
        sf.write(current_player);

        Game& game = Game::instance();
        game.get_display()->clear_display();

        HighScoreScreen hss(game.get_display(), sf.get_entries());
        auto val = hss.display();

        sf.save();
      }
    }
    catch (const std::runtime_error& e)
    {
      cout << e.what() << endl;
    }
  }
}

// Update the calendar based on how much time elapsed to this creature's action
void Game::process_elapsed_time(Calendar& calendar, const ActionCost& next_action_cost)
{
  double seconds = ActionCostConverter::to_seconds(next_action_cost.get_cost(), get_current_map()->get_map_type());
  calendar.add_seconds(seconds);
  time_keeper.tick(seconds);
}

// Update the calendar based on how much time has elapsed in seconds.
// The game loop itself should likely never call this - this is mainly intended
// for the scripting engine.
//
// Assumes the calendar attached to the current world.
void Game::process_elapsed_time(const int seconds)
{
  Calendar& calendar = get_current_world()->get_calendar();
  double d_sec = static_cast<double>(seconds);
  calendar.add_seconds(d_sec);
  time_keeper.tick(d_sec);
}

// Get and process the action for the current creature
ActionCost Game::process_action_for_creature(CreaturePtr current_creature, MapPtr c_map, const bool reloaded_game)
{
  ActionCost action_cost;
  Log& log = Log::instance();
  MapPtr current_map = c_map;

  if (current_creature)
  {
    // Don't try to get an action for the creature if it cannot act.  Instead,
    // increment the creature's turn by its current speed.
    CurrentCreatureAbilities cca;
    if (cca.can_act(current_creature) == false)
    {
      ActionCost acost;
      acost.set_cost(current_creature->get_speed().get_current());

      return acost;
    }

    DecisionStrategy* strategy = current_creature->get_decision_strategy();

    if (strategy)
    {
      bool advance = false;
      
      while (!advance)
      {
        // Comment/un-comment this as necessary to figure out if creatures are taking too long to process turns.
        //boost::timer::auto_cpu_timer timer;

        // Refresh the map.  Even if the turn doesn't advance, the map might
        // need reloading - e.g., moving off a map/descending a staircase
        // while timewalking.
        MapPtr g_curr_map = Game::instance().get_current_map();

        if (current_map && g_curr_map && g_curr_map->get_map_id() != current_map->get_map_id())
        {
          current_map = g_curr_map;
        }

        // Skip the creature's action if it is not the player, and does not have LOS of the player.
        // This is necessary for speedup purposes when there are lots of creatures on the map.
        CreaturePtr player = get_current_player();

        if (current_creature->get_is_player() == false)
        {
          // The player shared pointer might be null (creature might be acting before the player
          // has been officially placed on the map).  Advance (skip) the creature's turn in this
          // case.
          if (!player)
          {
            action_cost.set_cost(current_creature->get_speed().get_current());
            advance = true;
            continue;
          }
          else
          {
            // Quick and dirty - check to see if the tile distance between the player
            // and the creature is more than the creature's LOS.
            int distance = CoordUtils::chebyshev_distance(current_map->get_location(player->get_id()), current_map->get_location(current_creature->get_id()));

            // For now, burn a creature's action (do nothing!) if the creature falls outside
            // of the player's default LOS.
            if (distance > LineOfSightCalculator::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH)
            {
              action_cost.set_cost(current_creature->get_speed().get_current());
              advance = true;
              continue;
            }
          }
        }
 
        LineOfSightCalculator losc;
        TimeOfDayType tod = GameUtils::get_date(Game::instance()).get_time_of_day();
        int los_len = losc.calculate_los_length(current_creature, current_map->get_map_type(), tod);
        Coordinate creature_coords = current_map->get_location(current_creature->get_id());
        MapPtr view_map = ViewMapTranslator::create_view_map_around_tile(current_creature, current_map, creature_coords, los_len);
        MapPtr fov_map = CreatureUtils::update_fov_map(current_map, view_map, current_creature);
        
        if (current_creature->get_is_player())
        {
          // Do a full redraw if we've changed map, or if we've just reloaded the game.
          update_display(current_creature, current_map, fov_map, reloaded_game);

          // Now that we're about to process the player's action, clear the symbol
          // cache.
          Game::instance().get_map_registry_ref().clear_symbol_cache();
        }

        // Display what's been done in the last turn.
        display->refresh_current_window();

        // strategy is used for the creature's decision strategy, so use another
        // variable as the strategy for explicitly getting a command.  This might
        // not actually be the creature's strategy, but rather another one,
        // such as automatic movement, etc.
        //
        // The decision strategy might be a copy of the creature's, or might be
        // an altogether new one, which is why a unique_ptr is used.
        DecisionStrategyPtr command_strategy = DecisionStrategySelector::select_decision_strategy(current_creature);
        CommandPtr command = command_strategy->get_decision(true, current_creature->get_id(), game_command_factory.get(), game_kb_command_map.get(), fov_map /* view_map */);
        
        if (log.debug_enabled())
        {
          ostringstream ss;
          ss << current_creature->get_id() << " performs " << command->get_name();
          log.debug(ss.str());
        }

        // Clear the stored messages if we're about to receive the player's action.
        // The player will already have had a chance to read the messages.  The
        // exception to this is if the creature is automatically moving - we don't
        // want to clear the messages in this case, as otherwise when we get the
        // player's next action input, the messages will be gone.
        if (current_creature->get_is_player() && command->get_allow_clear_message_buffer())
        {
          MMF::instance().clear_if_necessary();
        }

        action_cost = CommandProcessor::process(current_creature, command.get(), display);

        if (current_creature->get_is_player() && get_is_current_map(current_map))
        {
          // After everything's done we need to update the display, but
          // shouldn't need to do a full redraw, since a full redraw
          // was done earlier in this function.
          update_display(current_creature, current_map, fov_map, false);
        }

        // Poor NPCs...they're discriminated against even at the code level!
        advance = action_cost.get_turn_advanced();

        // Ensure that NPCs always advance the turn, otherwise we'll run into
        // infinite loops.        
        if (!advance && !current_creature->get_is_player())
        {
          action_cost.set_cost(std::max(current_creature->get_speed().get_current() + 1, 1));
          advance = true;
        }

        if (advance)
        {
          // Call the stealth skill processor's ::process function.  This will
          // reduce the number of free hidden actions, and if the count went
          // from 1 to 0, add an appropriate message.
          //
          // If the creature was not hidden, this function does nothing.
          StealthSkillProcessor ssp;
          ssp.process(current_creature, current_map);
        }
      }
      
      // Update the current creature 
      CreatureCalculator cc;
      cc.update_calculated_values(current_creature);
      
      // Also update its number of turns, as long as we should keep playing
      // (player hasn't saved, been killed, and so on)
      if (keep_playing)
      {
        current_creature->increment_turns();
      }
    }
  }
  
  return action_cost;
}

void Game::stop_playing(CreaturePtr creature, const bool show_quit_actions, const bool delete_savefile)
{
  keep_playing = false;
  sound->stop_music(true);

  if (show_quit_actions && creature != nullptr && creature->get_is_player())
  {
    Game& game = Game::instance();

    if (String::to_bool(game.get_settings_ref().get_setting(Setting::PROMPT_FOR_CHARACTER_DUMP_ON_EXIT)))
    {
      // Prompt the player if they want an identified character dump created.
      IMessageManager& manager = MMF::instance();

      ExitGameAction ega;
      ega.create_dump_if_necessary(manager, &actions, creature);
    }

    if (delete_savefile)
    {
      string current_savefile = game.get_current_loaded_savefile();

      if (!current_savefile.empty())
      {
        Serialization::delete_savefile(current_savefile);
      }
    }    
  }
}

bool Game::should_keep_playing() const
{
  return keep_playing;
}

void Game::reload_map()
{
  reload_game_loop = true;
}

void Game::detect_creatures_if_necessary(CreaturePtr player, const string& original_map_id)
{
  DetectionSkillProcessor detection;
  
  if (original_map_id != current_map_id)
  {
    detection.process(player, get_current_map());
  }
}

// Set the current map in the map registry.
void Game::set_current_map(MapPtr map)
{
  // Unload the current map
  string old_map_id = current_map_id;
  MapPtr old_map = map_registry.get_map(old_map_id);
  
  if (!old_map || !old_map->get_permanent())
  {
    map_registry.remove_map(old_map_id); // Boom.
  }
  
  // Make the new map the current, and set it if it's not already in the
  // registry.
  current_map_id = map->get_map_id();
  map_registry.set_map(current_map_id, map);

  // Do an initial calculation of all the FOV maps and rebuild the temporary
  // data structures.
  map->reset_creatures_and_creature_locations();
  MapUtils::calculate_fov_maps_for_all_creatures(map);
}

// SHOULD ONLY BE SET BY UNIT TESTS THAT NEED A TEMPORARY WORLD
void Game::set_current_world(WorldPtr new_world)
{
  world = std::move(new_world);
}

// Get the current map from the map registry.
MapPtr Game::get_current_map() const
{
  return map_registry.get_map(current_map_id);
}

bool Game::get_is_current_map(MapPtr map) const
{
  bool is_curr = false;

  if (map != nullptr && map->get_map_id() == current_map_id)
  {
    return is_curr = true;
  }

  return is_curr;
}

ActionManager& Game::get_action_manager_ref()
{
  return actions;
}

ActionCoordinator& Game::get_action_coordinator_ref()
{
  return ac;
}

DeityActionManager& Game::get_deity_action_manager_ref()
{
  return deity_actions;
}

ScriptEngine& Game::get_script_engine_ref()
{
  return script_engine;
}

Mortuary& Game::get_mortuary_ref()
{
  return mortuary;
}

Quests& Game::get_quests_ref()
{
  return quests;
}

void Game::set_sid_ini_filename(const string& new_sid_ini_filename)
{
  sid_ini_filename = new_sid_ini_filename;
}

string Game::get_sid_ini_filename() const
{
  return sid_ini_filename;
}

void Game::set_scripts(const map<string, string>& new_scripts)
{
  scripts = new_scripts;
}

string Game::get_script(const string& script_name)
{
  string script;

  auto script_it = scripts.find(script_name);

  if (script_it != scripts.end())
  {
    script = script_it->second;
  }

  return script;
}

map<string, string> Game::get_scripts() const
{
  return scripts;
}

World* Game::get_current_world()
{
  return world.get();
}

LoadedMapDetails& Game::get_loaded_map_details_ref()
{
  return loaded_map_details;
}

void Game::set_current_loaded_savefile(const string& new_current_loaded_savefile)
{
  current_loaded_savefile = new_current_loaded_savefile;
}

string Game::get_current_loaded_savefile() const
{
  return current_loaded_savefile;
}

void Game::set_spritesheets(const map<string, pair<string, unordered_map<string, Coordinate>>>& new_spritesheets)
{
  spritesheets = new_spritesheets;
}

std::map<string, pair<string, unordered_map<string, Coordinate>>> Game::get_spritesheets() const
{
  return spritesheets;
}

void Game::set_count_score(const bool new_count_score)
{
  count_score = new_count_score;
}

bool Game::get_count_score() const
{
  return count_score;
}

double Game::get_total_elapsed_game_time(const std::chrono::system_clock::time_point& current_time) const
{
  return total_seconds_played + std::chrono::duration_cast<std::chrono::seconds>(current_time - game_start_time).count();
}

void Game::set_game_start_time(const std::chrono::system_clock::time_point& new_start_time)
{
  game_start_time = new_start_time;
}

std::chrono::system_clock::time_point Game::get_game_start_time() const
{
  return game_start_time;
}

void Game::update_player_dates()
{
  CreaturePtr player = Game::instance().get_current_player();

  // Update the end date on the player every turn in case they end up dying, etc.
  if (player != nullptr)
  {
    ostringstream ss;
    Date d = get_current_world()->get_calendar().get_date();
    d.serialize(ss);
    string cur_date_str = ss.str();

    if (player->get_additional_property(CreatureProperties::CREATURE_PROPERTIES_CHARACTER_STARTED).empty())
    {
      player->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_CHARACTER_STARTED, cur_date_str);
    }

    player->set_additional_property(CreatureProperties::CREATURE_PROPERTIES_GAME_DATE, cur_date_str);
  }
}

bool Game::serialize(ostream& stream) const
{
  Log::instance().trace("Game::serialize - start");

  // Ignore requires_redraw
  // Ignore keep_playing
  Serialize::write_bool(stream, reload_game_loop);

  settings.serialize(stream);

  // Ignore game_instance - it's a singleton, and the write/read code is already handling it
  Serialize::write_class_id(stream, display->get_class_identifier());
  display->serialize(stream);

  Serialize::write_class_id(stream, sound->get_class_identifier());
  sound->serialize(stream);

  map_registry.serialize(stream);

  Serialize::write_size_t(stream, sound_effects.size());
  for (const auto& se_pair : sound_effects)
  {
    Serialize::write_string(stream, se_pair.first.first);
    Serialize::write_string(stream, se_pair.first.second);

    Serialize::write_string(stream, se_pair.second);
  }

  music.serialize(stream);

  Serialize::write_size_t(stream, deities.size());
  for (const auto& deity_pair : deities)
  {
    Deity* deity = deity_pair.second.get();

    if (deity)
    {
      Serialize::write_string(stream, deity_pair.first);
      deity->serialize(stream);
    }
  }

  // Ignore race map - this will be built up on startup.
  // Ignore class map - this will be built up on startup.
  // Ignore creature map - this will be built up on startup.
  // Ignore spell map - this will be built up on startup.

  // The creature generation values map needs to be serialized because it
  // contains information on the current and maximum allowable values for
  // generation.
  size_t cgv_size = creature_generation_values.size();
  Serialize::write_size_t(stream, cgv_size);

  if (cgv_size > 0)
  {
    for (const CreatureGenerationValuesMap::value_type& cgv_val : creature_generation_values)
    {
      Serialize::write_string(stream, cgv_val.first);
      cgv_val.second.serialize(stream);
    }
  }

  // Item generation values
  size_t igv_size = item_generation_values.size();
  Serialize::write_size_t(stream, igv_size);

  if (igv_size > 0)
  {
    for (const GenerationValuesMap::value_type& igv_val : item_generation_values)
    {
      Serialize::write_string(stream, igv_val.first);
      igv_val.second.serialize(stream);
    }
  }

  // Item map needs to be serialized - the master item template contain
  // identification details that are otherwise lost when the game is saved
  // and subsequently loaded.
  Serialize::write_size_t(stream, items.size());
  
  string item_id;
  ItemPtr item;
  for (const ItemMap::value_type& item_pair : items)
  {
    item_id = item_pair.first;
    Serialize::write_string(stream, item_id);

    item = item_pair.second;
    
    if (item)
    {
      Serialize::write_class_id(stream, item->get_class_identifier());
      item->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
    }
  }

  Serialize::write_size_t(stream, configurable_features.size());

  for (const auto& feat_pair : configurable_features)
  {
    Serialize::write_string(stream, feat_pair.first);

    if (feat_pair.second)
    {
      Serialize::write_class_id(stream, feat_pair.second->get_class_identifier());
      feat_pair.second->serialize(stream);
    }
    else
    {
      Serialize::write_class_id(stream, ClassIdentifier::CLASS_ID_NULL);
    }
  }

  // Ignore tile_info map - this will be built up on startup.

  // Serialize the world
  world->serialize(stream);
  
  // Serialize the current map ID
  Serialize::write_string(stream, current_map_id);

  actions.serialize(stream);

  // deity_actions is stateless, and doesn't need to be saved.

  ac.serialize(stream);
    
  time_keeper.serialize(stream);

  script_engine.serialize(stream);

  mortuary.serialize(stream);

  quests.serialize(stream);

  // Ignore sid ini filename.

  // Game command factory and keyboard map get built up every time - don't save these.

  // Persist the map-redraw values so that the same logic can be applied after
  // a game is reloaded.
  loaded_map_details.serialize(stream);

  Serialize::write_string(stream, current_loaded_savefile);
  
  Serialize::write_size_t(stream, spritesheets.size());
  
  for (auto ss_pair : spritesheets)
  {
    string ss_id = ss_pair.first;
    pair<string, unordered_map<string, Coordinate>> fname_and_refs = ss_pair.second;

    Serialize::write_string(stream, ss_id);
    Serialize::write_string(stream, fname_and_refs.first);
    Serialize::write_size_t(stream, fname_and_refs.second.size());

    for (auto fr_pair : fname_and_refs.second)
    {
      Serialize::write_string(stream, fr_pair.first);
      Serialize::write_int(stream, fr_pair.second.first);
      Serialize::write_int(stream, fr_pair.second.second);
    }
  }

  Serialize::write_size_t(stream, calendar_days.size());

  for (const auto& cd_pair : calendar_days)
  {
    Serialize::write_int(stream, cd_pair.first);
    cd_pair.second.serialize(stream);
  }

  Serialize::write_size_t(stream, starting_locations.size());

  for (const auto& sl_pair : starting_locations)
  {
    Serialize::write_string(stream, sl_pair.first);
    sl_pair.second.serialize(stream);
  }

  Serialize::write_bool(stream, count_score);

  // We keep track of total seconds, but not start time, etc.
  double total_elapsed_time = get_total_elapsed_game_time(std::chrono::system_clock::now());
  Serialize::write_double(stream, total_elapsed_time);

  Serialize::write_bool(stream, is_loading);

  Log::instance().trace("Game::serialize - end");

  return true;
}

void Game::run_map_scripts()
{
  // After the custom maps have been set into the registry, we need to run
  // any custom load scripts on the maps.
  MapRegistryMap& mrm = map_registry.get_maps_ref();

  for (const auto& mrm_pair : mrm)
  {
    MapPtr map = mrm_pair.second;
    string load_script;

    EventScriptsMap esm = map->get_event_scripts();
    auto esm_it = esm.find(MapEventScripts::MAP_EVENT_SCRIPT_CREATE);

    if (esm_it != esm.end())
    {
      ScriptDetails sd = esm_it->second;
      ScriptEngine& se = Game::instance().get_script_engine_ref();
      MapScript ms;

      if (RNG::percent_chance(sd.get_chance()))
      {
        // JCD FIXME: Future events should be ms.execute_create, execute_something_else, etc.
        ms.execute(se, sd.get_script(), map);
      }
    }
  }
}

bool Game::deserialize(istream& stream)
{
  Log::instance().trace("Game::deserialize - start");

  // Ignore requires_redraw
  // Ignore keep_playing
  Serialize::read_bool(stream, reload_game_loop);
  // Ignore game_instance - it's a singleton, and the write/read code is already handling it
  
  settings.deserialize(stream);

  ClassIdentifier display_ci;
  Serialize::read_class_id(stream, display_ci);

  // Read and ignore the display.
  DisplayFactory di;
  pair<DisplayPtr, ControllerPtr> dc_pair = di.create_display_details(display_ci);

  if (!dc_pair.first) return false;
  if (!dc_pair.first->deserialize(stream)) return false;

  // We need the saved palette ID, however, so the user can see the last
  // palette they were using when they saved.
  display->set_palette(dc_pair.first->get_palette_id());

  // We also need the value of ASCII mode.
  display->set_force_ascii(dc_pair.first->get_force_ascii());

  ClassIdentifier sound_ci;
  Serialize::read_class_id(stream, sound_ci);

  SoundFactory sf;
  SoundPtr old_sound = sf.create_sound(sound_ci);
  old_sound->deserialize(stream);

  // Likewise with display and the palette ID/etc: get various sound
  // settings so these can persist between saves.
  sound->set_enable_sound(old_sound->get_enable_sound());
  sound->set_enable_sound_effects(old_sound->get_enable_sound_effects());
  sound->set_enable_ambient_sound_effects(old_sound->get_enable_ambient_sound_effects());
  sound->set_enable_music(old_sound->get_enable_music());

  map_registry.deserialize(stream);

  size_t se_size = 0;
  Serialize::read_size_t(stream, se_size);

  for (size_t i = 0; i < se_size; i++)
  {
    string id;
    string match;
    string location;

    Serialize::read_string(stream, id);
    Serialize::read_string(stream, match);
    Serialize::read_string(stream, location);

    pair<string, string> id_and_match = std::make_pair(id, match);
    sound_effects[id_and_match] = location;
  }

  music.deserialize(stream);

  size_t size = 0;
  Serialize::read_size_t(stream, size);
  deities.clear();

  for (size_t i = 0; i < size; i++)
  {
    string deity_id;
    DeityPtr deity = std::make_unique<Deity>();

    Serialize::read_string(stream, deity_id);
    deity->deserialize(stream);

    deities.insert(make_pair(deity_id, std::move(deity)));
  }

  // Ignore race map - this will be built up on startup.
  // Ignore class map - this will be built up on startup.
  // Ignore creature map - this will be built up on startup.
  // Ignore spell map - this will be built up on startup.

  // Keep track of creature generation values for the current/maximum allowable
  // generation amounts.
  size_t cgv_size = 0;
  Serialize::read_size_t(stream, cgv_size);

  if (cgv_size > 0)
  {
    creature_generation_values.clear();

    for (uint i = 0; i < cgv_size; i++)
    {
      string creature_id;
      Serialize::read_string(stream, creature_id);

      CreatureGenerationValues cgv;
      cgv.deserialize(stream);

      creature_generation_values.insert(make_pair(creature_id, cgv));
    }
  }

  // Keep track of item generation values for current/maximum allowed,
  // same as for creatures.
  size_t igv_size = 0;
  Serialize::read_size_t(stream, igv_size);

  if (igv_size > 0)
  {
    item_generation_values.clear();

    for (uint i = 0; i < igv_size; i++)
    {
      string item_id;
      Serialize::read_string(stream, item_id);

      GenerationValues gv;
      gv.deserialize(stream);

      item_generation_values.insert(make_pair(item_id, gv));
    }
  }

  // Item map needs to be serialized - the msater item template contain
  // identification details that are otherwise lost when the game is saved
  // and subsequently loaded.
  size_t num_itemmap_items = 0;
  Serialize::read_size_t(stream, num_itemmap_items);
  ClassIdentifier curitem_clid;
  string item_id;

  if (num_itemmap_items > 0)
  {
    items.clear();

    for (uint i = 0; i < num_itemmap_items; i++)
    {
      Serialize::read_string(stream, item_id);
      Serialize::read_class_id(stream, curitem_clid);

      if (curitem_clid != ClassIdentifier::CLASS_ID_NULL)
      {
        ItemPtr item = ItemSerializationFactory::create_item(curitem_clid);
        if (!item) return false;
        if (!item->deserialize(stream)) return false;

        items.insert(make_pair(item_id, item));
      }
    }
  }

  configurable_features.clear();
  size_t num_config_features = 0;
  Serialize::read_size_t(stream, num_config_features);

  for (size_t i = 0; i < num_config_features; i++)
  {
    string feature_id;
    Serialize::read_string(stream, feature_id);
    
    ClassIdentifier c_id = ClassIdentifier::CLASS_ID_NULL;
    Serialize::read_class_id(stream, c_id);

    if (c_id != ClassIdentifier::CLASS_ID_NULL)
    {
      FeaturePtr feat = FeatureGenerator::create_feature(c_id);

      if (feat != nullptr)
      {
        feat->deserialize(stream);
        configurable_features[feature_id] = feat;
      }
    }
  }

  // Ignore tile_info map - this will be built up on startup.

  // Deserialize the world
  world = std::make_unique<World>();
  if (!world) return false;
  if (!world->deserialize(stream)) return false;

  // Read the current map ID
  Serialize::read_string(stream, current_map_id);

  actions.deserialize(stream);

  // deity_actions is stateless, and doesn't need to be saved.
    
  ac.deserialize(stream);

  time_keeper.deserialize(stream);

  script_engine.deserialize(stream);

  mortuary.deserialize(stream);

  quests.deserialize(stream);

  // Ignore sid ini filename

  // Game command factory and keyboard map get built up every time - don't load these.

  loaded_map_details.deserialize(stream);

  Serialize::read_string(stream, current_loaded_savefile);

  size_t ss_size = 0;
  Serialize::read_size_t(stream, ss_size);

  for (size_t i = 0; i < ss_size; i++)
  {
    string ss_id;
    string ss_fname;

    Serialize::read_string(stream, ss_id);
    Serialize::read_string(stream, ss_fname);

    size_t refs_sz = 0;
    Serialize::read_size_t(stream, refs_sz);

    unordered_map<string, Coordinate> refs;

    for (size_t j = 0; j < refs_sz; j++)
    {
      string ref_id;
      int row = 0;
      int col = 0;

      Serialize::read_string(stream, ref_id);
      Serialize::read_int(stream, row);
      Serialize::read_int(stream, col);

      refs[ref_id] = {row, col};
    }

    spritesheets[ss_id] = {ss_fname, refs};
  }

  size_t cal_size = 0;
  Serialize::read_size_t(stream, cal_size);

  for (size_t i = 0; i < cal_size; i++)
  {
    int day_of_year = -1;
    Serialize::read_int(stream, day_of_year);

    CalendarDay day_info;
    day_info.deserialize(stream);

    calendar_days[day_of_year] = day_info;
  }

  size_t sl_sz = 0;
  Serialize::read_size_t(stream, sl_sz);
  starting_locations.clear();

  for (size_t i = 0; i < sl_sz; i++)
  {
    StartingLocation sl;
    string sl_id;

    Serialize::read_string(stream, sl_id);
    sl.deserialize(stream);

    starting_locations.insert(make_pair(sl_id, sl));
  }

  Serialize::read_bool(stream, count_score);
  Serialize::read_double(stream, total_seconds_played);
  Serialize::read_bool(stream, is_loading);

  Log::instance().trace("Game::deserialize - end");
  return true;
}

ClassIdentifier Game::internal_class_identifier() const
{
  return ClassIdentifier::CLASS_ID_GAME;
}

#ifdef UNIT_TESTS
#include "unit_tests/Game_test.cpp"
#endif
