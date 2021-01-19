require('map_events')

local wintersea_map_id = args[MAP_ID]

function init_wintersea_keep(map_id)
  generate_adventurer(map_id, 12, 0, 1)
end

map_events.set_map_fn(wintersea_map_id, init_wintersea_keep)
