require('constants')
require('fn')
require('map_events')

local map_id = "isen_dun"

local function init_seagarden(map_id)
  local item_ids = {BLUE_WILDFLOWER_ID, CYAN_WILDFLOWER_ID, WHITE_WILDFLOWER_ID}

  for x = 68, 76 do
    add_object_to_map(item_ids[RNG_range(1, #item_ids)], map_id, 16, x)
  end

  add_object_to_map(SHOVEL_ID, map_id, RNG_range(15, 16), 67)
end

local function init_pier_garden(map_id)
  generate_vegetable_garden(map_id, 12, 15, 51, 54, true, 1, 1)
end

local function init_kew_items(map_id)
  local kew_items = {{FIRE_BOMB_ID,2,64,4},{UNSTONING_POTION_ID,2,64,1},{STONE_HAMMER_ID,2,64,1},{DIGGING_WAND_ID,2,65,1},{METAL_CAP_ID,2,65,1},{BUCKLER_ID,2,66,1},{PICK_AXE_ID,6,75,1},{HEALING_POTION_ID,6,76,1},{UNSTONING_POTION_ID,6,76,1}}

  for i,v in ipairs(kew_items) do
    -- Kews items shouldn't be generated cursed.
    add_object_to_map(v[1], map_id, v[2], v[3], v[4], true)
  end
end

local function init_isen_dun(map_id)
  init_seagarden(map_id)
  init_pier_garden(map_id)
  init_kew_items(map_id)
end

map_events.set_map_fn(map_id, init_isen_dun)

