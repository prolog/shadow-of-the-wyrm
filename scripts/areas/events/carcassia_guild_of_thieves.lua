require('generate')

-- TODO: The right half of the map should be accessible only by digging,
-- and should contain a series of overlapping rooms, populated by undead,
-- filled with treasure.

local function init_carcassia_guild_of_thieves(map_id)
  local mem_ids = {"urchin", "thief", "blackguard"}
  local num_creatures = RNG_range(10, 18)
  
  generate.add_creatures(map_id, {12, 2}, {17, 31}, mem_ids, num_creatures)
end

map_events.set_map_fn("carcassia_guild_of_thieves", init_carcassia_guild_of_thieves)
