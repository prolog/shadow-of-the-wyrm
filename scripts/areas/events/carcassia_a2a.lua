require('carcassia_common')
require('constants')
require('map_events')

local map_id = "carcassia_a2a"

function init_sky_high_deals(map_id)
  local y_start = RNG_range(5, 6)
  local height = (9 - y_start) * 2 + 1
  local x_start = 55, 56
  local width = (62 - x_start) * 2
  local gen_door = false

  local walkway_end_x = x_start + width - 1

  generate_shop(map_id, y_start, x_start, height, width, CTILE_TYPE_AIR, gen_door)

  -- Since we've generated air around the shop, reconnect the shop with the
  -- walkway.
  map_transform_tile(map_id, 9, walkway_end_x, CTILE_TYPE_DUNGEON)

  log(CLOG_ERROR, "Transformed tile at 9," .. tostring(walkway_end_x))
end

function init_carcassia_a2a(map_id)
  init_sky_high_deals(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_a2a)

