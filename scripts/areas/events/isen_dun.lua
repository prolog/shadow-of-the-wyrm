require('constants')
require('fn')
require('map_events')

local map_id = "isen_dun"

local function init_seagarden(map_id)
  local item_ids = {BLUE_WILDFLOWER_ID, CYAN_WILDFLOWER_ID, WHITE_WILDFLOWER_ID}

  for x = 68, 76 do
    add_object_to_map(item_ids[RNG_range(1, #item_ids)], map_id, 16, x)
  end

  add_object_to_map(SHOVEL_ID, map_id, RNG_range(15, 16), 67)
end

local function init_isen_dun(map_id)
  init_seagarden(map_id)
end

map_events.set_map_fn(map_id, init_isen_dun)

