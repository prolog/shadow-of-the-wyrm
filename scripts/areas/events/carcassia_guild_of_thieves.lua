require('generate')

local function init_guild(map_id)
  local mem_ids = {"urchin", "thief", "blackguard"}
  local num_creatures = RNG_range(10, 18)

  generate.add_creatures(map_id, {12, 2}, {17, 31}, mem_ids, num_creatures, false)
end

local function init_creatures(map_id, placements, creature_ids)
  local num_creatures = RNG_range(#placements * 1.5, #placements * 3)

  for i = 1, num_creatures do
    local cr_id = creature_ids[RNG_range(1, #creature_ids)]
    local room = placements[RNG_range(1, #placements)]
    local y = RNG_range(room[1], room[3])
    local x = RNG_range(room[2], room[4])

    add_creature_to_map(cr_id, y, x, map_id)
  end
end

local function init_treasure(map_id, placements, treasure_ids)
  local num_items = RNG_range(#placements, #placements * 1.5)

  for i = 1, num_items do
    local item_id = treasure_ids[RNG_range(1, #treasure_ids)]
    local room = placements[RNG_range(1, #placements)]
    local y = RNG_range(room[1], room[3])
    local x = RNG_range(room[2], room[4])

    add_object_to_map(item_id, map_id, y, x)
  end
end

local function init_tombs(map_id)
  local creature_ids = {"mummy", "golem", "corpse_fiend", "shadow_snake", "skeletal_warrior", "muck", "mire", "rock_grinder", "shade", "crone"}
  local treasure_ids = {"gain_attributes_potion", "speed_potion", "antidote_potion", "_ether_potion", "identify_scroll", "enchanting_scroll", "mapping_scroll", "recharging_scroll", "teleport_wand", "dragon_breath_wand", "digging_wand", "_golden_apple", "_silver_apple", "silverweed"}

  local placements = dig_rectangles(map_id, 1, 1, 10, 40, 8)
  local placements2 = dig_rectangles(map_id, 1, 35, 18, 78, 8)

  for i = 1, #placements2 do
    table.insert(placements, placements2[i])
  end

  init_treasure(map_id, placements, treasure_ids)
  init_creatures(map_id, placements, creature_ids)
end

local function init_carcassia_guild_of_thieves(map_id)
  init_guild(map_id)
  init_tombs(map_id)
end

map_events.set_map_fn("carcassia_guild_of_thieves", init_carcassia_guild_of_thieves)
