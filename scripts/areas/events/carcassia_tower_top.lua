require('generate')

local function init_flying_creatures(map_id)
  local cr_ids = {"rook", "blood_hawk", "falcon", "shimmering_cloud", "grifin"}
  local num_creatures = RNG_range(10, 15)

  --generate.add_creatures(map_id, {0, 7}, {18, 29}, cr_ids, num_creatures)
  --generate.add_creatures(map_id, {0, 61}, {18, 75}, cr_ids, num_creatures)
end

local function init_carcassia_tower_top(map_id)
  init_flying_creatures(map_id)
end

map_events.set_map_fn("carcassia_tower_top", init_carcassia_tower_top)
