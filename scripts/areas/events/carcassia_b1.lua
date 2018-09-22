require('fn')
require('map_events')

local map_id = "carcassia_b1"

local function setup_keep_rooms(m_id)
  local coords = {{14,10}, {14,31}}
  local feature_class_ids = {CCLASS_ID_FORGE, CCLASS_ID_TANNERY, CCLASS_ID_JEWELER_WORKBENCH, CCLASS_ID_WHEEL_AND_LOOM}

  for i,coord in ipairs(coords) do
    local cl_id = feature_class_ids[RNG_range(1, #feature_class_ids)]

    add_feature_to_map(cl_id, coord[1], coord[2], map_id)
  end
end

local function setup_dynamic_content(m_id)
  setup_keep_rooms(m_id)

  if carcassia_garden_type == nil then
    -- See ResidentialSectorFeatureGenerator.hpp
    carcassia_garden_type = RNG_range(1, 2)
  end

  local gt = carcassia_garden_type

  -- Always rocks alongside the palace.
  generate_city_feature(m_id, 13, 3, 18, 4, CCITY_SECTOR_RESIDENTIAL, 0)

  -- Either rocks or wildflowers in front of the palace.
  generate_city_feature(m_id, 13, 37, 18, 56, CCITY_SECTOR_RESIDENTIAL, gt)
  generate_city_feature(m_id, 13, 60, 18, 79, CCITY_SECTOR_RESIDENTIAL, gt)

  -- Features along the road to the fortress.
  generate_city_feature(m_id, 1, 45, 4, 57, CCITY_SECTOR_RESIDENTIAL)
  generate_city_feature(m_id, 1, 59, 4, 78, CCITY_SECTOR_RESIDENTIAL)
  generate_city_feature(m_id, 7, 39, 11, 56, CCITY_SECTOR_RESIDENTIAL)
  generate_city_feature(m_id, 7, 60, 11, 78, CCITY_SECTOR_RESIDENTIAL)
end

local function setup_praetor_house(map_id)
  -- Need to do the quests in order to see the praetor - no cheating by
  -- digging!
  for row = 2,10 do
    for col = 7,34 do
      map_set_tile_property(map_id, row, col, "TILE_PROPERTY_CANNOT_DIG", "1")
    end
  end
end
 
function init_carcassia_b1(map_id)
  setup_dynamic_content(map_id)
  setup_praetor_house(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_b1)

