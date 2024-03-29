require('constants')
require('fn')
require('map_events')
require('carcassia_common')

local map_id = "carcassia_a2"
local population = {"_potter", "_farmer", "_small_child", "seawife", "_commoner", "thief", "urchin", "blackguard", "rat", "gnomish_sailor", "_fisherman", "carcassian_guard", "layperson", "tradesman", "merchant", "_vendor", "traveller", "_drunk"}

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
    set_event_script(cr_id, map_id, "move/carcassia_turtles.lua", CCREATURE_EVENT_SCRIPT_ENTER_TILE, 100)
  end
end

local function setup_dynamic_content(map_id)
  -- South of the casino is always a graveyard
  generate_city_feature(map_id, 11, 4, 18, 18, CCITY_SECTOR_LOW_INCOME_RESIDENTIAL, 1)

  -- For the rest of the city features, generate random coordinates, and
  -- try to place the feature, checking first to make sure the area's
  -- clear.  Because there will be a lot of places where things can't be
  -- generated, run the algorithm a number of times to try to luck out.
  for i=1,80 do
    local y = RNG_range(3,10)
    local y2 = y + RNG_range(6,9)

    local x = RNG_range(20,70)
    local x2 = x + RNG_range(6, 10)

    -- Ensure that each feature has a "border" of passable tiles around
    -- it so that the map remains connected.
    if map_do_tiles_in_range_match_type(map_id, y, x, y2, x2, CTILE_TYPE_FIELD) then
      generate_city_feature(map_id, y+1, x+1, y2-1, x2-1, CCITY_SECTOR_LOW_INCOME_RESIDENTIAL)
    end
  end

end

function init_carcassia_a2(map_id)
  setup_casino(map_id)
  setup_turtle_track(map_id)
  setup_dynamic_content(map_id)
  carcassia_common.setup_population(map_id, {8,20}, {18,75}, population)
end

map_events.set_map_fn(map_id, init_carcassia_a2)

