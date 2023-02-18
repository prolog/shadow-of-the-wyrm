require('carcassia_common')
require('constants')
require('map_events')

local map_id = "carcassia_a2a"

function init_sky_high_deals(map_id)
  local width = RNG_range(4, 6)
  local max_x = 66 - width
  local height = RNG_range(4, 6)
  local max_y = 19 - height
  local shopkeeper_name = "Sal"
  local gen_walls_and_door = false

  generate_shop(RNG_range(0, max_y), RNG_range(0, max_x), height, width, shopkeeper_name, gen_walls_and_door)
end

function init_carcassia_a2a(map_id)
  init_sky_high_deals(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_a2a)

