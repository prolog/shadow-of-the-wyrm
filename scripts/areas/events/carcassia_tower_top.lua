require('generate')

local function init_lorelei_room(map_id)
  local row = 14
  local items = {"_wildflower_1", "_wildflower_2", "_wildflower_3", "_wildflower_4", "_wildflower_5", "_wildflower_6"}

  for col = 35,42 do
    item_id = items[RNG_range(1, #items)]
    add_object_to_map(item_id, map_id, row, col)
  end
end

local function init_flying_creatures(map_id)
  local cr_ids = {"rook", "blood_hawk", "falcon", "shimmering_cloud", "griffin"}
  local num_creatures = RNG_range(10, 15)
  local hostile = true

  generate.add_creatures(map_id, {0, 7}, {18, 29}, cr_ids, num_creatures, hostile)
  generate.add_creatures(map_id, {0, 61}, {18, 75}, cr_ids, num_creatures, hostile)
end

local function init_carcassia_tower_top(map_id)
  init_lorelei_room(map_id)
  init_flying_creatures(map_id)
end

map_events.set_map_fn("carcassia_tower_top", init_carcassia_tower_top)
