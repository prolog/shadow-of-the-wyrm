require('fn')
require('map_events')

local map_id = "carcassia_c2"

local function setup_entrance_features(map_id)
  local class_id = CCLASS_ID_FOUNTAIN
  
  for row = 1,7 do
    local col1 = 16
    local col2 = 24
    class_id = CCLASS_ID_FOUNTAIN

    if row % 2 == 0 then
      col1 = 17
      col2 = 23
      class_id = CCLASS_ID_FIRE_PILLAR
    end

    add_feature_to_map(class_id, row, col1, map_id)
    add_feature_to_map(class_id, row, col2, map_id)
  end

  class_id = CCLASS_ID_FIRE_PILLAR

  for row = 11, 18, 2 do
    add_feature_to_map(class_id, row, 17, map_id)
    add_feature_to_map(class_id, row, 23, map_id)
  end
end

function init_carcassia_c2(map_id)
  setup_entrance_features(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_c2)

