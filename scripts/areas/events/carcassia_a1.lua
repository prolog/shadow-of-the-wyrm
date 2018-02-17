require('fn')
require('map_events')

local map_id = "carcassia_a1"

-- JCD FIXME: Consider making this a generic Lua API function in the
-- engine.
function setup_parklands_around_treasure_room(map_id)
  if RNG_percent_chance(50) then
    map_fill_random(map_id, 2, 3, 9, 11, CTILE_TYPE_FIELD, CTILE_TYPE_TREE, 50)
  else
    map_fill_staggered(map_id, 2, 3, 9, 11, CTILE_TYPE_FIELD, CTILE_TYPE_TREE, RNG_range(2, 3))
  end
end

function setup_nodig_treasure_room_and_traps(map_id)
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

  -- Add some thieves and urchins along the north wall.
  for i = 1, RNG_range(3,5) do
    local c_idx = RNG_range(1, #coords)
    local cr_coord = coords[c_idx]
    local cr_id = "thief"

    if RNG_percent_chance(50) then
      cr_id = "urchin"
    end

    add_creature_to_map(cr_id, cr_coord[1], cr_coord[2], map_id)
  end

  -- Set the teleporter from the closed room to just outside the gate.
  set_trap(4, 8, false, teleport_trap_id, map_id)
  set_feature_additional_property(map_id, 4, 8, teleport_loc_prop, "10,1")
end

function init_carcassia_a1(map_id)
  setup_parklands_around_treasure_room(map_id)
  setup_nodig_treasure_room_and_traps(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_a1)

