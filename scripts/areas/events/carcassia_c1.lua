require('fn')
require('map_events')

local map_id = "carcassia_c1"

local function init_throne_room()
  local rows = {4,14}
  local start_col = 6

  for i,row in ipairs(rows) do
    for col = start_col, 54, 5 do
      add_feature_to_map(CCLASS_ID_FIRE_PILLAR, row, col, map_id)
    end
  end

  for row = 4, 14, 2 do
    add_feature_to_map(CCLASS_ID_FIRE_PILLAR, row, start_col, map_id)
  end
end

function init_carcassia_c1(map_id)
  init_throne_room(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_c1)

