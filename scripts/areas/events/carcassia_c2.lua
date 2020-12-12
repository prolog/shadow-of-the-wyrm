require('carcassia_common')
require('constants')
require('fn')
require('map_events')

local map_id = "carcassia_c2"
local population = {"urchin", "_commoner", "drunk", "_farmer", "_noble"}

local function setup_special_features(map_id)
  map_set_tile_property(map_id, 9, 47, "TILE_PROPERTY_ALLOWED_CREATURE_IDS", PLAYER_ID)
end

local function setup_arena_litter(map_id)
  local litter_ids = {"dagger", "mace", "broad_sword", "spear", "_cap", "buckler", "sling"}

  for row = 6,12 do
    for col = 54,62 do
      if RNG_percent_chance(10) then
        add_object_to_map(INTACT_SKELETON_ID, map_id, row, col)
      elseif RNG_percent_chance(10) then
        add_object_to_map(litter_ids[RNG_range(1, #litter_ids)], map_id, row, col)
      end
    end
  end
end

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

local function setup_west_room_features(map_id)
  -- Fountains
  local rows = {4, 14}
  
  for i,y in ipairs(rows) do
    for x = 6,8 do
      add_feature_to_map(CCLASS_ID_FOUNTAIN, y, x, map_id)
    end
  end

  -- Statues
  rows = {1, 18}
  local class_ids = {CCLASS_ID_WARLORD_DECORATIVE_STATUE, CCLASS_ID_KNIGHT_DECORATIVE_STATUE}

  for i,y in ipairs(rows) do
    for x = 1, 13, 2 do
      add_feature_to_map(class_ids[RNG_range(1, #class_ids)], y, x, map_id)
    end
  end
end

function init_carcassia_c2(map_id)
  setup_special_features(map_id)
  setup_west_room_features(map_id)
  setup_entrance_features(map_id)
  setup_arena_litter(map_id)
  carcassia_common.setup_population(map_id, {4,28}, {16,43}, population)
end

map_events.set_map_fn(map_id, init_carcassia_c2)

