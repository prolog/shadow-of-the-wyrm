require('constants')
require('fn')
require('map_events')

local map_id = "forest_of_yew"

local function init_community_garden(map_id)
  generate_vegetable_garden(map_id, 1, 4, 57, 62, false, 1, 1)
end

local function init_yew(map_id)
  init_community_garden(map_id)
end

map_events.set_map_fn(map_id, init_yew)

