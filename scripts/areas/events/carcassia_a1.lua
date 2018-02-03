require('map_events')

local map_id = "carcassia_a1"

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

  local traps = {{teleport_trap_id, teleport_loc_prop, "4,7"}}--,
--                 {"blackwater_trap"}, 
  --               {"monster_trap"}}

  for i = 1, #traps do
    local row, col = 2, RNG_range(3, 78)

    if RNG_percent_chance(50) then
      row, col = RNG_range(2, 18), 3
    end

    local trap = traps[i]
    set_trap(row, col, false, trap[1], map_id)

    -- If there are any properties for the trap, then set them.
    if table.getn(trap) == 3 then
      set_feature_additional_property(map_id, row, col, trap[2], trap[3])
    end
  end

  -- Set the teleporter from the closed room to just outside the gate.
  set_trap(4, 8, false, teleport_trap_id, map_id)
  set_feature_additional_property(map_id, 4, 8, teleport_loc_prop, "10,1") 
end

function init_carcassia_a1(map_id)
  setup_nodig_treasure_room_and_traps(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_a1)

