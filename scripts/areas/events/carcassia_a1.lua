require('map_events')

local map_id = "carcassia_a1"

function init_carcassia_a1(map_id)
  -- Ensure the teleport room is no-dig, while keeping the rest of
  -- the map diggable.
  for row = 3,5 do
    for col = 5,9 do
      map_set_tile_property(map_id, row, col, "TILE_PROPERTY_CANNOT_DIG", "1")
    end
  end      
end

map_events.set_map_fn(map_id, init_carcassia_a1)

