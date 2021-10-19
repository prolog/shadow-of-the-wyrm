require('constants')
require('fn')
require('map_events')

local map_id = "whalings_end"

local function init_community_garden(map_id)
  generate_vegetable_garden(map_id, 16, 18, 11, 13, false, 1, 1)
end

local function init_yew(map_id)
  init_community_garden(map_id)
end

map_events.set_map_fn(map_id, init_yew)

