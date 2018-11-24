module(..., package.seeall)

function add_creatures(map_id, start_coord, end_coord, creature_ids, num_creatures, hostility_val)
  local avail_coords = map_get_available_creature_coords(map_id, start_coord[1], start_coord[2], end_coord[1], end_coord[2])

  for i = 1, num_creatures do
    if #avail_coords == 0 then
      return
    end

    local cr_id = creature_ids[RNG_range(1, #creature_ids)]
    local coord_idx = RNG_range(1, #avail_coords)
    local coord = avail_coords[coord_idx]
    local y = coord[1]
    local x = coord[2]
    table.remove(avail_coords, coord_idx)

    -- Check the coordinates to make sure the creature can be placed
    -- there.
    local tile_details = map_get_tile(map_id, y, x)
    local tile_type = tile_details["tile_type"]
    
    if tile_type ~= nil and tile_type ~= CTILE_TYPE_UP_STAIRCASE and tile_type ~= CTILE_TYPE_DOWN_STAIRCASE then
      add_creature_to_map(cr_id, y, x, map_id, hostility_val)
    end
  end
end

