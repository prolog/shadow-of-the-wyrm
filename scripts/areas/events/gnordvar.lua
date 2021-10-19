require('constants')
require('fn')
require('map_events')

local map_id = "gnordvar"

local function init_community_garden(map_id)
  generate_vegetable_garden(map_id, 7, 11, 39, 44, true, 1, 1)
end

local function init_gnordvar(map_id)
  init_community_garden(map_id)
end

map_events.set_map_fn(map_id, init_gnordvar)

