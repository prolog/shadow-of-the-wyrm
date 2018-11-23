require('carcassia_common')
require('fn')
require('map_events')

local map_id = "carcassia_c1"
local population = {"noble", "carcassian_guard"}

local function init_altar_annex()
  for row = 11,18,2 do
    add_feature_to_map(CCLASS_ID_FIRE_PILLAR, row, 55, map_id)
    add_feature_to_map(CCLASS_ID_FIRE_PILLAR, row, 61, map_id)
  end
end

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
  init_altar_annex(map_id)
  carcassia_common.setup_population(map_id, {6,25}, {12,47}, population)
end

map_events.set_map_fn(map_id, init_carcassia_c1)

