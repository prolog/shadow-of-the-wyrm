require('constants')
require('fn')
require('map_events')

local map_id = "carcassia_a1"

local function setup_adventurers_in_the_inn(map_id)
  generate_adventurer(map_id, 17, 65, 1)
  generate_adventurer(map_id, 17, 67, 1)
end

local function setup_tomb_guardians(map_id)
  map_set_property(map_id, "MAP_PROPERTIES_TOMB_GUARDIANS", "skeletal_warrior,mummy")
end

-- JCD FIXME: Consider making this a generic Lua API function in the
-- engine.
local function setup_parklands_around_treasure_room(map_id)
  local tile_type = CTILE_TYPE_TREE

  if RNG_percent_chance(33) then
    tile_type = CTILE_TYPE_EVERGREEN_TREE
  end

  if RNG_percent_chance(50) then
    map_fill_random(map_id, 2, 3, 7, 11, CTILE_TYPE_FIELD, tile_type, 50)
  else
    map_fill_staggered(map_id, 2, 3, 7, 11, CTILE_TYPE_FIELD, tile_type, RNG_range(2, 3))
  end
end

local function setup_nodig_treasure_room_and_traps(map_id)
  -- Ensure the teleport room is no-dig, while keeping the rest of
  -- the map diggable.
  for row = 3,5 do
    for col = 5,9 do
      map_set_tile_property(map_id, row, col, "TILE_PROPERTY_CANNOT_DIG", "1")
    end
  end

  -- Set a few traps around the inner edge of the wall.  One of them is
  -- a teleporter into the sealed room.
  local teleport_trap_id = "teleport_trap"
  local teleport_loc_prop = "EFFECT_PROPERTIES_TELEPORT_LOCATION"

  local coords = fn.make_coordinates(2,2,3,78)
  local c_idx = RNG_range(1, #coords)
  local trap_coords = coords[c_idx]
  local row, col = trap_coords[1], trap_coords[2]

  set_trap(row, col, false, "teleport_trap", map_id)
  set_feature_additional_property(map_id, row, col, teleport_loc_prop, "4,7")
  table.remove(coords, c_idx)
  local gen_guild_key = false

  -- Add some thieves and urchins along the north wall.
  for i = 1, RNG_range(3,5) do
    local c_idx = RNG_range(1, #coords)
    local cr_coord = coords[c_idx]
    local cr_id = "thief"

    if RNG_percent_chance(50) then
      cr_id = "urchin"
    end

    local cr_uid = add_creature_to_map(cr_id, cr_coord[1], cr_coord[2], map_id)

    -- One of the local no-goodniks will have a key to the door in the
    -- abandoned part of the guild of thieves.
    if gen_guild_key == false then
      gen_guild_key = add_object_to_creature(map_id, cr_uid, TEMPLATE_KEY_ID, "lock_id=guild_of_thieves")
    end
  end

  -- Set the teleporter from the closed room to just outside the gate.
  set_trap(4, 8, false, teleport_trap_id, map_id)
  set_feature_additional_property(map_id, 4, 8, teleport_loc_prop, "10,1")
end

local function setup_dynamic_content(map_id)
  generate_city_feature(map_id, 3, 15, 8, 30, CCITY_SECTOR_PUBLIC_AREA)
  generate_city_feature(map_id, 12, 15, 18, 30, CCITY_SECTOR_PUBLIC_AREA)
  generate_city_feature(map_id, 3, 58, 8, 67, CCITY_SECTOR_PUBLIC_AREA)
  generate_city_feature(map_id, 3, 70, 9, 78, CCITY_SECTOR_PUBLIC_AREA)
end

local function init_carcassia_a1(map_id)
  setup_adventurers_in_the_inn(map_id)
  setup_tomb_guardians(map_id)
  setup_parklands_around_treasure_room(map_id)
  setup_nodig_treasure_room_and_traps(map_id)
  setup_dynamic_content(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_a1)

