require('fn')
require('map_events')

local map_id = "carcassia_b2"

function init_carcassia_b2(map_id)
  set_trap(10, 55, false, monster_trap, map_id)
end

map_events.set_map_fn(map_id, init_carcassia_b2)

