require('carcassia_common')
require('constants')
require('map_events')

local map_id = "carcassia_a2a"

function init_carcassia_a2a(map_id)
  -- JCD FIXME add the sky-high deals
end

map_events.set_map_fn(map_id, init_carcassia_a2a)

