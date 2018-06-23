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

function init_carcassia_a2(map_id)
  setup_casino(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_a2)

