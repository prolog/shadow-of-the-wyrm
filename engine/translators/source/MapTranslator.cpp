#include <algorithm>
#include "common.hpp"
#include "Conversion.hpp"
#include "CreatureCoordinateCalculator.hpp"
#include "Display.hpp"
#include "Game.hpp"
#include "GameUtils.hpp"
#include "LineOfSightCalculator.hpp"
#include "Log.hpp"
#include "MapDisplayArea.hpp"
#include "MapProperties.hpp"
#include "MapTranslator.hpp"
#include "MapUtils.hpp"
#include "RNG.hpp"
#include "Setting.hpp"
#include "WeatherCalculator.hpp"

using namespace std;

MapTranslator::MapTranslator()
{
}

MapTranslator::~MapTranslator()
{
}

DisplayMap MapTranslator::create_display_map(CreaturePtr creature, const bool player_blinded, const MapPtr& map, const MapPtr& fov_map, const MapDisplayArea& display_area, const Coordinate& reference_coords, const bool full_redraw_required)
{
  Coordinate display_coords = CreatureCoordinateCalculator::calculate_display_coordinate(display_area, map, reference_coords);
  LineOfSightCalculator losc;
  TimeOfDayType tod = GameUtils::get_date(Game::instance()).get_time_of_day();
  int los_len = losc.calculate_los_length(creature, map->get_map_type(), tod);
  int actual_row, actual_col;

  // Get the current season and set it into the copy.
  // Get the time information, too, for overriding colours for day/night.
  Game& game = Game::instance();
  Calendar& calendar = game.get_current_world()->get_calendar();
  Season season = calendar.get_season()->get_season();
  MapPtr current_map = game.get_current_map();
  Date date = calendar.get_date();
  Settings& settings = game.get_settings_ref();
  pair<Colour, Colour> tod_overrides = TimeOfDay::get_time_of_day_colours(date.get_time_of_day(), MapUtils::get_supports_time_of_day(current_map->get_map_type()), settings.get_setting_as_bool(Setting::SHADE_TERRAIN), settings.get_setting_as_bool(Setting::SHADE_CREATURES_AND_ITEMS));
  vector<Colour> scv = String::create_colour_vector_from_csv_string(map->get_property(MapProperties::MAP_PROPERTIES_SHIMMER_COLOURS));
  bool timewalking = false;

  // Stepping out of time should disallow shimmer colours!
  if (creature && creature->has_status(StatusIdentifiers::STATUS_ID_TIMEWALK))
  {
    timewalking = true;
  }

  ShimmerColours shimmer_colours(scv);

  int cursor_row = reference_coords.first;
  int cursor_col = reference_coords.second;
  Coordinate engine_coord = CreatureCoordinateCalculator::calculate_engine_coordinate(display_area, map, reference_coords);

  uint start_y, start_x;
  uint stop_y, stop_x;
  Dimensions map_dim = map->size();

  string map_id;

  if (map != nullptr)
  {
    map_id = map->get_map_id();
  }

  // Ensure that we're not trying to walk over the maximum size of our map.
  int display_height = std::min<int>(map_dim.get_y(), display_area.get_height());
  int display_width = std::min<int>(map_dim.get_x(), display_area.get_width());
  DisplayMap display_map(map_id, display_area.get_height(), display_area.get_width());

  // Set the loop's start/stop points based on whether a full redraw is
  // required.  It may have been required as part of the display coordinate
  // calculations done as part of this function!
  if (full_redraw_required)
  {
    // We can use the full display, so go from 0 to display_height/display_width.
    start_y = 0;
    stop_y = display_height;
    start_x = 0;
    stop_x = display_width;
  }
  else
  {
    start_y = std::max<int>(0, display_coords.first - los_len - 1);
    stop_y = std::min<int>(display_height, display_coords.first + los_len + 2);
    start_x = std::max<int>(0, display_coords.second - los_len - 1);
    stop_x = std::min<int>(display_width, display_coords.second + los_len + 2);
  }

  for (uint d_row = start_y; d_row < stop_y; d_row++)
  {
    for (uint d_col = start_x; d_col < stop_x; d_col++)
    {
      // Create the display coordinate.  Note that this can be different
      // from the actual engine coordinate!
      //
      // E.g, if the player is at 90, 30
      // and the display is 80x20
      //
      // The display's (col 0, row 0) will start at 80, 20 on the real
      // map, and the player will be at 10, 10 relative to this.
      Coordinate dc(d_row, d_col);

      actual_row = engine_coord.first + d_row;
      actual_col = engine_coord.second + d_col;

      DisplayTile display_tile = translate_coordinate_into_display_tile(creature, player_blinded, timewalking, tod_overrides, shimmer_colours, map, fov_map, actual_row, actual_col);

      // Set the cursor coordinates.  Update the game's tracked display
      // coordinates, so that a full redraw can be performed.
      if ((actual_row == cursor_row) && (actual_col == cursor_col))
      {
        display_map.set_cursor_coordinate(dc);
      }

      display_tile.set_season(season);

      // Set the display tile
      display_map.set(dc, display_tile);
    }
  }

  return display_map;
}

// Create a display tile from a given coordinate, given the current map
// and the current FOV map.
DisplayTile MapTranslator::translate_coordinate_into_display_tile(const CreaturePtr& creature, const bool player_blinded, const bool timewalking, const pair<Colour, Colour>& tod_overrides, const ShimmerColours& shimmer_colours, const MapPtr& map, const MapPtr& fov_map, const int actual_row, const int actual_col)
{
  // Get the map tile
  TilePtr map_tile = map->at(actual_row, actual_col);
      
  // Check to see if a corresponding FOV tile exists
  TilePtr fov_map_tile;
  if (fov_map != nullptr)
  {
    fov_map_tile = fov_map->at(actual_row, actual_col);
  }

  // Translate the map tile
  return create_display_tile(creature, player_blinded, timewalking, tod_overrides, shimmer_colours, map_tile, fov_map_tile, actual_row, actual_col);
}

// Create the tile to display, based on the tile's properties, and whether or
// not the player's been blinded.  If the player's been blinded, the tile will
// be black, unless it is the player's tile, in which case the player will be
// displayed.
DisplayTile MapTranslator::create_display_tile(const CreaturePtr& perspective_creature, const bool player_blinded, const bool timewalking, const pair<Colour, Colour>& tod_overrides, const ShimmerColours& shimmer_colours, const TilePtr& actual_tile, const TilePtr& fov_tile, const int row, const int col)
{
  DisplayTile display_tile;

  // Is it a FOV tile, and is the player not blinded?
  // Special case for blindness - does the tile contain the player?  Because
  // we always want to show the player.
  if ((fov_tile && !player_blinded) || (player_blinded && fov_tile && fov_tile->get_creature() && fov_tile->get_creature()->get_is_player()))
  {
    CreaturePtr creature = actual_tile->get_creature();
    IInventoryPtr inv = actual_tile->get_items();
    FeaturePtr feature = actual_tile->get_feature();

    // If a creature exists on this tile - will be null if the ptr is not init'd.
    // Display the creature if the player is not blind, or if the player is the
    // creature (presumably, the player always has a sense of where they are!).
    if (creature)
    {
      display_tile = create_display_tile_from_creature(creature, tod_overrides.second);
    }
    else if (!inv->empty() && !player_blinded) // If at least one item exists in the tile's inventory of items
    {
      ItemPtr item = inv->at(0); // Get the first item

      if (item != nullptr)
      {
        display_tile = create_display_tile_from_item(item, tod_overrides.second);
      }
    }
    else if (feature && !feature->get_is_hidden() && !player_blinded) // There's no creature, and no items.  Is there a feature?  Can it be seen?
    {
      display_tile = create_display_tile_from_feature(feature, timewalking, tod_overrides.second, shimmer_colours);
    }
    else // Nothing else, or the player is blind - display the tile only.
    {
      display_tile = create_display_tile_from_tile(perspective_creature, actual_tile, timewalking, tod_overrides, shimmer_colours, row, col);
    }      
  }
  else
  {
    if (actual_tile && actual_tile->get_explored() && !player_blinded)
    {
      display_tile = create_unseen_and_explored_display_tile(perspective_creature, actual_tile, timewalking, tod_overrides, shimmer_colours, row, col);
    }
    else
    {
      if (actual_tile && actual_tile->get_viewed() && !player_blinded)
      {
        display_tile = create_unseen_and_previously_viewed_display_tile(perspective_creature, actual_tile, timewalking, tod_overrides, shimmer_colours, row, col);
      }
      else
      {
        display_tile = create_unseen_and_unexplored_display_tile();
      }
    }
  }

  return display_tile;
}

// Create a display tile from a given creature
DisplayTile MapTranslator::create_display_tile_from_creature(const CreaturePtr& creature, const Colour override_colour)
{
  Symbol symbol('?', Colour::COLOUR_WHITE);

  if (creature != nullptr)
  {
    symbol = creature->get_symbol();
  }

  return create_display_tile_from_symbol_and_colour(symbol, override_colour != Colour::COLOUR_UNDEFINED ? override_colour : creature->get_symbol().get_colour());
}

// Create a display tile from a given tile feature
DisplayTile MapTranslator::create_display_tile_from_feature(const FeaturePtr& feature, const bool timewalking, const Colour override_colour, const ShimmerColours& map_shimmer_colours)
{
  Colour colour = Colour::COLOUR_UNDEFINED;
  ShimmerColours shimmer_colours = map_shimmer_colours;

  if (feature->has_shimmer_colours())
  {
    shimmer_colours = feature->get_shimmer_colours();
  }

  int pct_chance_shimmer = shimmer_colours.get_pct_chance_shimmer();

  if (timewalking)
  {
    pct_chance_shimmer = 0;
  }

  Colour shimmer_colour = RNG::percent_chance(pct_chance_shimmer) ? shimmer_colours.get_shimmer_colour() : shimmer_colours.get_feature_colour();
  Symbol s('?', Colour::COLOUR_WHITE);

  if (feature != nullptr)
  {
    s = feature->get_symbol();
    colour = feature->get_colour();
  }

  if (override_colour != Colour::COLOUR_UNDEFINED)
  {
    colour = override_colour;
  }

  if (shimmer_colour != Colour::COLOUR_UNDEFINED)
  {
    colour = shimmer_colour;
  }

  return create_display_tile_from_symbol_and_colour(s, colour);
}

// Create a display tile from a given item
DisplayTile MapTranslator::create_display_tile_from_item(const ItemPtr& item, const Colour override_colour)
{
  bool apply_override = (override_colour != Colour::COLOUR_UNDEFINED && !item->get_glowing());
  Colour colour = item->get_colour();

  if (apply_override)
  {
    colour = override_colour;
  }

  Symbol s('?', Colour::COLOUR_WHITE);
  
  if (item != nullptr)
  {
    s = item->get_symbol();
  }

  return create_display_tile_from_symbol_and_colour(s, colour);
}

// Create a display tile from a given tile
DisplayTile MapTranslator::create_display_tile_from_tile(const CreaturePtr& creature, const TilePtr& tile, const bool timewalking, const pair<Colour, Colour> tod_overrides, const ShimmerColours& shimmer_colours, const int row, const int col)
{
  DisplayTile display_tile;
  Game& game = Game::instance();
  Colour override_colour = tod_overrides.first;
  MapRegistry& mr = game.get_map_registry_ref();
  MapPtr map = game.get_current_map();
  MapType mt = MapType::MAP_TYPE_OVERWORLD;

  // Deathly tiles are drained of all colour, and appear black.
  // We don't properly check the creature because these tiles
  // should always appear visually dark, regardless if they are
  // eg water tiles and the creature has a boat, which would
  // allow the creature to remain safe.
  if (tile->get_unprotected_movement_is_death(nullptr))
  {
    override_colour = Colour::COLOUR_BOLD_BLACK;
  }
  
  // Almost always not null, except when using the MapTester config.
  if (map != nullptr)
  {
    mt = map->get_map_type();
  }

  const vector<DisplayTile>& tiles_info = game.get_tile_display_info_ref();
  DisplayTile tile_info = tiles_info.at(static_cast<int>(tile->get_tile_type()));
  display_tile = tile_info;

  bool passable = tile && (tile->get_movement_multiplier() > 0);
  Colour shimmer_colour = Colour::COLOUR_UNDEFINED;
  
  int pct_chance_shimmer = shimmer_colours.get_pct_chance_shimmer();

  WeatherCalculator wc;
  WeatherPtr weather = MapUtils::get_weather(map, tile);
  int pct_chance_weathered = 0;
  
  if (weather != nullptr)
  {
    pct_chance_weathered = wc.calculate_pct_chance_shimmer(map, weather->get_wind_speed());
  }

  string cache_key = MapUtils::convert_coordinate_to_map_key({row, col});
  auto cache_details = mr.cache_has_symbol(cache_key);

  if (timewalking || cache_details.first)
  {
    pct_chance_shimmer = 0;
    pct_chance_weathered = 0;
  }

  if (RNG::percent_chance(pct_chance_shimmer))
  {
    shimmer_colour = shimmer_colours.get_shimmer_colour();
  }
  else
  {
    if (passable)
    {
      shimmer_colour = shimmer_colours.get_passable_colour();
    }
    else
    {
      shimmer_colour = shimmer_colours.get_impassable_colour();
    }
  }

  if (cache_details.first)
  {
    // If the tile is cached (e.g., it's a shimmer colour that we
    // want to hold until the player's next turn), ensure that the
    // shimmer colour is set so it'll take the same value as the
    // previous redraw.
    shimmer_colour = cache_details.second.get_colour();
  }

  // If weather is affecting the tile:
  //
  // 1. Use the TOD overrides if they exist
  // 2. Otherwise, pick one at random from the allowable values
  vector<Colour> weather_colours = display_tile.get_weather_colours();
  
  if (!weather_colours.empty() && RNG::percent_chance(pct_chance_weathered))
  {
    if (override_colour != Colour::COLOUR_UNDEFINED)
    {
      if (RNG::percent_chance(50))
      {
        shimmer_colour = tod_overrides.first;
      }
      {
        shimmer_colour = tod_overrides.second;
      }
    }
    else
    {
      shimmer_colour = weather_colours.at(RNG::range(0, weather_colours.size() - 1));
    }
  }

  if (shimmer_colour != Colour::COLOUR_UNDEFINED)
  {
    override_colour = shimmer_colour;
  }

  if (override_colour != Colour::COLOUR_UNDEFINED)
  {
    display_tile.set_all_colours(static_cast<int>(override_colour));
  }

  // Update the cache for the turn
  Symbol s = display_tile.get_symbol();
  s.set_colour(shimmer_colour);

  if (mt == MapType::MAP_TYPE_WORLD)
  {
    if (MapUtils::has_known_treasure(tile, creature, false))
    {
      display_tile = create_display_tile_for_treasure();
    }

    if (MapUtils::has_known_shipwreck(map, tile, creature, false))
    {
      display_tile = create_display_tile_for_shipwreck();
    }
  }

  mr.add_symbol_to_cache(cache_key, s);

  return display_tile;
}

DisplayTile MapTranslator::create_display_tile_from_symbol_and_colour(const Symbol& symbol, const Colour colour)
{
  Symbol s = symbol;
  s.set_colour(colour);
  DisplayTile display_tile(s);
  
  return display_tile;  
}

DisplayTile MapTranslator::create_unseen_and_previously_viewed_display_tile(const CreaturePtr& creature, const TilePtr& tile, const bool timewalking, const pair<Colour, Colour>& tod_overrides, const ShimmerColours& shimmer_colours, const int row, const int col)
{
  return create_unseen_and_explored_display_tile(creature, tile, timewalking, tod_overrides, shimmer_colours, row, col);
}

DisplayTile MapTranslator::create_unseen_and_explored_display_tile(const CreaturePtr& creature, const TilePtr& tile, const bool timewalking, const pair<Colour, Colour>& tod_overrides, const ShimmerColours& shimmer_colours, const int row, const int col)
{
  DisplayTile display_tile;
  
  if (tile->has_feature() && !tile->get_feature()->get_is_hidden())
  {
    FeaturePtr feature = tile->get_feature();
    display_tile = create_display_tile_from_feature(feature, timewalking, tod_overrides.second, shimmer_colours);
  }
  else
  {
    display_tile = create_display_tile_from_tile(creature, tile, timewalking, tod_overrides, shimmer_colours, row, col);
  }

  return display_tile;
}

// Always black - no overrides!
DisplayTile MapTranslator::create_unseen_and_unexplored_display_tile()
{
  DisplayTile display_tile;
  
  Symbol s(' ', Colour::COLOUR_BLACK);
  display_tile.set_symbol(s);
  
  return display_tile;  
}

DisplayTile MapTranslator::create_display_tile_for_treasure()
{
  Symbol s;
  s.set_colour(Colour::COLOUR_BOLD_RED);
  
  SpritesheetLocation sl;
  sl.set_index(SpritesheetIndex::SPRITESHEET_INDEX_TERRAIN);
  sl.set_reference_id(SpritesheetReference::SPRITESHEET_REFERENCE_TREASURE);

  s.set_symbol('X');
  s.set_spritesheet_location(sl);

  return create_display_tile_from_symbol_and_colour(s, Colour::COLOUR_BOLD_RED);
}

DisplayTile MapTranslator::create_display_tile_for_shipwreck()
{
  Symbol s;
  s.set_colour(Colour::COLOUR_BOLD_CYAN);

  SpritesheetLocation sl;
  sl.set_index(SpritesheetIndex::SPRITESHEET_INDEX_TERRAIN);
  sl.set_reference_id(SpritesheetReference::SPRITESHEET_REFERENCE_SHIPWRECK);

  s.set_symbol('X');
  s.set_spritesheet_location(sl);

  return create_display_tile_from_symbol_and_colour(s, Colour::COLOUR_BOLD_CYAN);
}