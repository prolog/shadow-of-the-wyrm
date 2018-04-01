-- TODO: The right half of the map should be accessible only by digging,
-- and should contain a series of overlapping rooms, populated by undead,
-- filled with treasure.

-- JCD FIXME: This sort of function will be needed later in script -
-- make it generic and move it to a common Lua source file.
local function init_carcassia_guild_of_thieves(map_id)
  local mem_ids = {"urchin", "thief", "blackguard"}
  local num_creatures = RNG_range(10, 18)
  local avail_coords = map_get_available_creature_coords(map_id, 12, 2, 17, 31)

  for i = 1, num_creatures do
    if #avail_coords == 0 then
      return
    end

    local cr_id = mem_ids[RNG_range(1, #mem_ids)]
    local coord_idx = RNG_range(1, #avail_coords)
    local coord = avail_coords[coord_idx]
    table.remove(avail_coords, coord_idx)

    -- Check the coordinates to make sure the creature can be placed
    -- there.
    local tile_details = map_get_tile(map_id, coord[1], coord[2])
    local tile_type = tile_details["tile_type"]
  
    if tile_type ~= nil and tile_type ~= CTILE_TYPE_UP_STAIRCASE and tile_type ~= CTILE_TYPE_DOWN_STAIRCASE then
      add_creature_to_map(cr_id, coord[1], coord[2], map_id, false)
    end
  end
end

map_events.set_map_fn("carcassia_guild_of_thieves", init_carcassia_guild_of_thieves)
