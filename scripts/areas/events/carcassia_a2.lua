require('constants')
require('fn')
require('map_events')

local map_id = "carcassia_a2"

local function setup_casino(map_id)
  -- Ivory in the vault
  for y = 4,8 do
    for x = 15, 17 do
      add_object_to_map(CURRENCY_ID, map_id, y, x, RNG_range(100, 150))
    end
  end

  -- Add the key to one of the dealers at random
  local coords = {{4,7}, {4,11}}
  local coord = coords[RNG_range(1, #coords)]

  local creature_id = get_creature_id(coord[1], coord[2], map_id)
  add_object_to_creature(map_id, creature_id, "casino_key")
end

local function setup_turtle_track(map_id)
  -- Keep the player off the track
  for row = 4,6 do
    for col = 25,31 do
      map_set_tile_property(map_id, row, col, "TILE_PROPERTY_ALLOWED_RACES", "_animal")
    end
  end

  -- Make the turtles less bitey
  for row = 4,6 do
    local cr_id = get_creature_id(row, 25, map_id)
    set_hostility(cr_id, PLAYER_ID, map_id, false)
  end

  local turtle_details = {{4, 25, "TURTLE_NAME1_SID", 1}, 
                          {5, 25, "TURTLE_NAME2_SID", 3}, 
                          {6, 25, "TURTLE_NAME3_SID", 10}}

  -- Name the turtles and set their automove coordinates.
  for k,v in ipairs(turtle_details) do
    local cr_id = get_creature_id(v[1], v[2], map_id)

    set_creature_name(cr_id, get_sid(v[3]), map_id)
    set_creature_colour(cr_id, v[4], map_id)
    set_automove_coords(cr_id, map_id, v[1], 31)
    set_event_script(cr_id, map_id, "move/carcassia_turtles.lua", "CREATURE_EVENT_SCRIPT_ENTER_TILE", 100)
  end
end

local function setup_dynamic_content(map_id)
  -- South of the casino is always a graveyard
  generate_city_feature(map_id, 11, 4, 18, 18, CCITY_SECTOR_LOW_INCOME_RESIDENTIAL, 1)
end

function init_carcassia_a2(map_id)
  setup_casino(map_id)
  setup_turtle_track(map_id)
  setup_dynamic_content(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_a2)

