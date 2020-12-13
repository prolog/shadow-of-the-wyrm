require('carcassia_common')
require('fn')
require('map_events')

local map_id = "carcassia_c1"
local population = {"_noble", "carcassian_guard"}

local function init_altar_annex()
  for row = 11,18,2 do
    add_feature_to_map(CCLASS_ID_FIRE_PILLAR, row, 55, map_id)
    add_feature_to_map(CCLASS_ID_FIRE_PILLAR, row, 61, map_id)
  end
end

local function init_throne_room()
  local rows = {4,14}
  local statue_id_first = CCLASS_ID_KING_DECORATIVE_STATUE
  local statue_id_last = CCLASS_ID_SORCEROR_DECORATIVE_STATUE
  local start_col = 6

  for i,row in ipairs(rows) do
    for col = start_col, 54, 5 do
      add_feature_to_map(CCLASS_ID_FIRE_PILLAR, row, col, map_id)
    end
  end

  for row = 4, 14, 2 do
    add_feature_to_map(CCLASS_ID_FIRE_PILLAR, row, start_col, map_id)
  end

  -- Statues along the walls
  for x = 38, 48, 5 do
    add_feature_to_map(RNG_range(statue_id_first, statue_id_last), 1, x, map_id)
    add_feature_to_map(RNG_range(statue_id_first, statue_id_last), 1, x+1, map_id)
  end

  for x = 8, 48, 5 do
    add_feature_to_map(RNG_range(statue_id_first, statue_id_last), 18, x, map_id)
    add_feature_to_map(RNG_range(statue_id_first, statue_id_last), 18, x+1, map_id)
  end

  for y = 5, 13, 2 do
    add_feature_to_map(CCLASS_ID_KING_DECORATIVE_STATUE, y, 3, map_id)
  end
end

function init_carcassia_c1(map_id)
  init_throne_room(map_id)
  init_altar_annex(map_id)
  carcassia_common.setup_population(map_id, {6,25}, {12,47}, population)
end

map_events.set_map_fn(map_id, init_carcassia_c1)

