require('fn')
require('map_events')

local map_id = "carcassia_b1"

local function setup_dynamic_content(map_id)
  generate_city_feature(map_id, 13, 37, 18, 56, CCITY_SECTOR_RESIDENTIAL, 1)
  generate_city_feature(map_id, 13, 60, 18, 79, CCITY_SECTOR_RESIDENTIAL, 1)
end
 
function init_carcassia_b1(map_id)
  setup_dynamic_content(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_b1)

