#include <boost/timer/timer.hpp>
#include "global_prototypes.hpp"
#include "Conversion.hpp"
#include "CoordUtils.hpp"
#include "CreatureCalculator.hpp"
#include "CreatureDescriber.hpp"
#include "CreatureCoordinateCalculator.hpp"
#include "CreatureFeatures.hpp"
#include "CurrentCreatureAbilities.hpp"
#include "CursesProperties.hpp"
#include "CustomAreaGenerator.hpp"
#include "CursesConstants.hpp"
#include "DecisionStrategySelector.hpp"
#include "Detection.hpp"
#include "ExitGameAction.hpp"
#include "FieldOfViewStrategy.hpp"
#include "FieldOfViewStrategyFactory.hpp"
#include "FileConstants.hpp"
#include "Game.hpp"
#include "HighScoreScreen.hpp"
#include "CommandProcessor.hpp"
#include "CreatureTranslator.hpp"
#include "ItemSerializationFactory.hpp"
#include "Log.hpp"
#include "MapCursor.hpp"
#include "MapUtils.hpp"
#include "PlayerConstants.hpp"
#include "WorldGenerator.hpp"
#include "MapTranslator.hpp"
#include "DisplayStatistics.hpp"
#include "MessageManagerFactory.hpp"
#include "ScoreFile.hpp"
#include "ScoreTextKeys.hpp"
#include "Serialize.hpp"
#include "Serialization.hpp"
#include "StatusActionProcessor.hpp"
#include "TextKeys.hpp"
#include "TextMessages.hpp"
#include "ViewMapTranslator.hpp"
#include "WorldTimeKeeperCoordinator.hpp"
#include "WorldMapLocationTextKeys.hpp"

// Used by serialization code:
#include "CommandFactoryFactory.hpp"
#include "DisplayFactory.hpp"
#include "KeyboardCommandMapFactory.hpp"
#include "WorldFactory.hpp"

using namespace std;

Game::Game()
: keep_playing(true), reload_game_loop(false), current_world_ix(0)
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

// Set the settings, and also update any other settings (like the language
// file, etc) that are derived from the settings.
void Game::set_settings(const Settings& new_settings)
{
  settings = new_settings;

  string language_file = settings.get_setting("language_file");
  set_sid_ini_filename(language_file);

  string log_level = settings.get_setting("log_level");
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
  string cursor_mode = settings.get_setting("cursor_mode");
  CursorMode cm = static_cast<CursorMode>(String::to_int(cursor_mode));

  // Game may just be starting up.
  if (display != nullptr)
  {
    if (cm >= CursorMode::CURSOR_MODE_MIN && cm <= CursorMode::CURSOR_MODE_MAX)
    {
      DisplayPtr display = get_display();
      display->set_property(CursesProperties::CURSES_PROPERTIES_CURSOR_MODE, cursor_mode);
    }
  }
}
void Game::set_world_settings()
{
  uint days_elapsed = String::to_uint(settings.get_setting("days_elapsed"));
  WorldPtr world = get_current_world();

  // If we're just starting up, the world may not have been instantiated yet.
  if (world != nullptr)
  {
    world->get_calendar().set_date(days_elapsed);
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
  deities = game_deities;
}

const DeityMap& Game::get_deities_ref() const
{
  return deities;
}

void Game::set_races(const RaceMap& game_races)
{
  races = game_races;
}

const RaceMap& Game::get_races_ref() const
{
  return races;
}

void Game::set_classes(const ClassMap& game_classes)
{
  classes = game_classes;
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

void Game::set_custom_maps(const vector<MapPtr>& custom_maps)
{
  for (MapPtr custom_map : custom_maps)
  {
    string id = custom_map->get_map_id();
    map_registry.set_map(id, custom_map);
  }
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


CreaturePtr Game::get_current_player() const
{
  CreaturePtr current_player = get_current_map()->get_creature(PlayerConstants::PLAYER_CREATURE_ID);
  return current_player;
}

// Create the new world, and set the player at the special "player's starting location" point.
// Then, read in the XML areas, and overlay that on top.
void Game::create_new_world(CreaturePtr creature)
{
  WorldGenerator world_generator;
  MapPtr current_world = world_generator.generate();
  WorldPtr world(new World(current_world));
  worlds.push_back(world);
  current_world_ix = (worlds.size() - 1);

  set_world_settings();

  // Need to set the world map into the registry so that it's available to 
  // any scripts called by the CustomAreaGenerator.
  set_current_map(current_world);

  CustomAreaGenerator cag(FileConstants::WORLD_MAP_AREAS_FILE);
  cag.overlay_custom_areas(current_world);

  TilePtr tile = current_world->get_tile_at_location(WorldMapLocationTextKeys::STARTING_LOCATION);

  if (tile)
  {
    tile->set_creature(creature);

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
    bool redraw_needed = loaded_map_details.requires_full_map_redraw() || reloaded_game;

    CurrentCreatureAbilities cca;
    CreaturePtr player = game.get_current_player();

    DisplayMap display_map = MapTranslator::create_display_map(!cca.can_see(player), current_map, fov_map, display_area, reference_coords.first, redraw_needed);
    
    CursorSettings cs = CursorSettings::CURSOR_SETTINGS_USE_DEFAULT;

    if (reference_coords.second)
    {
      cs = CursorSettings::CURSOR_SETTINGS_SHOW_CURSOR;
    }

    if (redraw_needed)
    {
      display->draw(display_map, cs);
    }
    else
    {
      display->draw_update_map(display_map, cs);
    }

    // As long as there are still player actions within the current map, and we've
    // not loaded a new map, a full redraw is not needed:
    loaded_map_details.synch();
  }
}

void Game::go()
{
  game_command_factory = std::make_shared<CommandFactory>();
  game_kb_command_map = std::make_shared<KeyboardCommandMap>();

  set_check_scores(true);

  StatusActionProcessor sap;
  MapPtr current_map = get_current_map();
  CreaturePtr current_player = get_current_player();

  // Use a try-catch block so that if there is an exception thrown, we can
  // try to recover by saving.
  try
  {
    // To see if this is a new game, check the ActionCoordinator to see if there is
    // a map, yet.  If there isn't, the game hasn't been restored, so it must be a
    // new game.
    bool reloaded_game = !ac.get_current_map_id().empty();

    string welcome_message = TextMessages::get_welcome_message(current_player->get_name(), !reloaded_game);

    IMessageManager& manager = MessageManagerFactory::instance(current_player, true);
    manager.add_new_message(welcome_message);
    manager.send();

    CreatureCalculator::update_calculated_values(current_player);

    string map_id = "";

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

      Calendar& calendar = worlds[current_world_ix]->get_calendar();

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
        }

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

          CreatureStatusMap creature_statuses_before = current_creature->get_statuses();

          ActionCost action_cost = process_action_for_creature(current_creature, current_map, reloaded_game);
          sap.process_action(current_creature, creature_statuses_before, action_cost);

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
  actions.save(player);
}

void Game::set_check_scores(const bool new_check_scores)
{
  check_scores = new_check_scores;
}

bool Game::should_check_scores() const
{
  return check_scores;
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
      ScoreFile sf;
      bool sf_updated = sf.write(current_player);

      Game& game = Game::instance();
      HighScoreScreen hss(game.get_display(), sf.get_entries());
      hss.display();

      sf.save();
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
ActionCost Game::process_action_for_creature(CreaturePtr current_creature, MapPtr current_map, const bool reloaded_game)
{
  ActionCost action_cost;
  
  if (current_creature)
  {
    // Don't try to get an action for the creature if it cannot act.  Instead,
    // increment the creature's turn by its current speed.
    CurrentCreatureAbilities cca;
    if (cca.can_act(current_creature) == false)
    {
      ActionCost ac;
      ac.set_cost(current_creature->get_speed().get_current());

      return ac;
    }

    DecisionStrategyPtr strategy = current_creature->get_decision_strategy();

    if (strategy)
    {
      bool advance = false;
      
      while (!advance)
      {
        // Comment/un-comment this as necessary to figure out if creatures are taking too long to process turns.
        //boost::timer::auto_cpu_timer timer;
        MapPtr view_map;
        MapPtr fov_map;

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
            // of the player's LOS.
            if (distance > CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH)
            {
              action_cost.set_cost(current_creature->get_speed().get_current());
              advance = true;
              continue;
            }
          }
        }

        Coordinate creature_coords = current_map->get_location(current_creature->get_id());
        view_map = ViewMapTranslator::create_view_map_around_tile(current_map, creature_coords, CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH /* FIXME */);
        
        FieldOfViewStrategyPtr fov_strategy = FieldOfViewStrategyFactory::create_field_of_view_strategy(current_creature->get_is_player());
        fov_map = fov_strategy->calculate(current_creature, view_map, creature_coords, CreatureConstants::DEFAULT_CREATURE_LINE_OF_SIGHT_LENGTH /* FIXME */);

        if (strategy)
        {
          strategy->set_fov_map(fov_map);
        }
        
        if (current_creature->get_is_player())
        {
          // Do a full redraw if we've changed map, or if we've just reloaded the game.
          update_display(current_creature, current_map, fov_map, reloaded_game);
        }

        // strategy is used for the creature's decision strategy, so use another
        // variable as the strategy for explicitly getting a command.  This might
        // not actually be the creature's strategy, but rather another one,
        // such as automatic movement, etc.
        DecisionStrategyPtr command_strategy = DecisionStrategySelector::select_decision_strategy(current_creature);
        CommandPtr command = command_strategy->get_decision(true, current_creature->get_id(), game_command_factory, game_kb_command_map, view_map /* fov_map */);
        
        // Clear the stored messages if we're about to receive the player's action.
        // The player will already have had a chance to read the messages.  The
        // exception to this is if the creature is automatically moving - we don't
        // want to clear the messages in this case, as otherwise when we get the
        // player's next action input, the messages will be gone.
        if (current_creature->get_is_player() && command->get_allow_clear_message_buffer())
        {
          MessageManagerFactory::instance(current_creature, true).clear_if_necessary();
        }

        action_cost = CommandProcessor::process(current_creature, command, display);

        if (current_creature->get_is_player())
        {
          // Do a full redraw if we've changed map, or if we've just reloaded the game.
          update_display(current_creature, current_map, fov_map, reloaded_game);
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
      }
      
      // Update the current creature 
      CreatureCalculator::update_calculated_values(current_creature);
      
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

  if (show_quit_actions && creature != nullptr && creature->get_is_player())
  {
    Game& game = Game::instance();

    if (String::to_bool(game.get_settings_ref().get_setting("prompt_for_character_dump_on_exit")))
    {
      // Prompt the player if they want an identified character dump created.
      IMessageManager& manager = MessageManagerFactory::instance();

      ExitGameAction ega;
      ega.create_dump_if_necessary(manager, &actions, creature);

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
  DetectionProcessor detection;
  
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
  
  // Make the new map the current
  current_map_id = map->get_map_id();
  map_registry.set_map(current_map_id, map);
}

// Get the current map from the map registry.
MapPtr Game::get_current_map() const
{
  return map_registry.get_map(current_map_id);
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

WorldPtr Game::get_current_world()
{
  WorldPtr world;

  // This function may be called before the game is properly set up.  If so,
  // just return a null shared ptr, and be prepared to check for it.
  if (!worlds.empty())
  {
    world = worlds[current_world_ix];
  }

  return world;
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

bool Game::serialize(ostream& stream) const
{
  Log::instance().trace("Game::serialize - start");

  // Ignore keep_playing
  Serialize::write_bool(stream, reload_game_loop);

  settings.serialize(stream);

  // Ignore game_instance - it's a singleton, and the write/read code is already handling it
  Serialize::write_class_id(stream, display->get_class_identifier());
  display->serialize(stream);

  map_registry.serialize(stream);

  Serialize::write_size_t(stream, deities.size());
  for (const auto& deity_pair : deities)
  {
    DeityPtr deity = deity_pair.second;

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

  // Ignore tile_info map - this will be built up on startup.

  size_t num_worlds = worlds.size();
  Serialize::write_size_t(stream, num_worlds);

  for (WorldPtr world : worlds)
  {
    world->serialize(stream);
  }

  Serialize::write_uint(stream, current_world_ix);
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
    
  Serialize::write_size_t(stream, calendar_days.size());

  for (const auto& cd_pair : calendar_days)
  {
    Serialize::write_int(stream, cd_pair.first);
    cd_pair.second.serialize(stream);
  }

  Log::instance().trace("Game::serialize - end");

  return true;
}

bool Game::deserialize(istream& stream)
{
  Log::instance().trace("Game::deserialize - start");

  // Ignore keep_playing
  Serialize::read_bool(stream, reload_game_loop);
  // Ignore game_instance - it's a singleton, and the write/read code is already handling it
  
  settings.deserialize(stream);

  ClassIdentifier display_ci;
  Serialize::read_class_id(stream, display_ci);
  display = DisplayFactory::create_display_details(display_ci).first;
  if (!display) return false;
  if (!display->deserialize(stream)) return false;

  map_registry.deserialize(stream);

  size_t size = 0;
  Serialize::read_size_t(stream, size);
  deities.clear();

  for (size_t i = 0; i < size; i++)
  {
    string deity_id;
    DeityPtr deity = make_shared<Deity>();

    Serialize::read_string(stream, deity_id);
    deity->deserialize(stream);

    deities.insert(make_pair(deity_id, deity));
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

  // Ignore tile_info map - this will be built up on startup.

  size_t num_worlds;
  Serialize::read_size_t(stream, num_worlds);

  worlds.clear();

  for (unsigned int i = 0; i < num_worlds; i++)
  {
    WorldPtr world = WorldFactory::create_world();
    if (!world) return false;
    if (!world->deserialize(stream)) return false;
    worlds.push_back(world);
  }

  Serialize::read_uint(stream, current_world_ix);
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