require('carcassia_common')
require('constants')
require('map_events')

local map_id = "carcassia_a2a"

function init_sky_high_deals(map_id)
  local y_start = RNG_range(5, 6)
  local height = (9 - y_start) * 2 + 1
  local x_start = 56, 57
  local width = (62 - x_start) * 2
  local gen_door = false

  local walkway_end_x = x_start + width - 1

  generate_shop(map_id, y_start, x_start, height, width, CTILE_TYPE_AIR, gen_door)

  -- Since we've generated air around the shop, reconnect the shop with the
  -- walkway.
  map_transform_tile(map_id, 9, walkway_end_x, CTILE_TYPE_DUNGEON)
end

local function add_guards_to_station(map_id, row, col_start, col_end)
  for x = col_start, col_end do
    if x % 6 == 0 then
      add_creature_to_map(CARCASSIAN_GUARD_ID, row, x, map_id)
    end
  end
end

local function add_equipment_to_station(map_id, row, col_start, col_end)
  local ammo = {ARROW_ID, BOLT_ID, JAVELIN_ID, BARBED_SPEAR_ID, THROWING_CLUB_ID}
  local rare_ammo = {EXPLODING_ARROW_ID, WINGED_JAVELIN_ID}
  for x = col_start, col_end do
    if RNG_percent_chance(60) then
      local ammo_id = ammo[RNG_range(1, #ammo)]

      if RNG_percent_chance(7) then
        ammo_id = rare_ammo[RNG_range(1, #rare_ammo)]
      end

      add_object_to_map(ammo_id, map_id, row, x)
    end
  end
end

local function init_first_row(map_id, first_row)
  local guard_station = RNG_percent_chance(100)

  local start_x = 6
  for x = start_x, 61 do
    map_transform_tile(map_id, first_row, x, CTILE_TYPE_DUNGEON)
  end

  if guard_station == true then
    local offsets = {-1, 1}

    for idx = 1, #offsets do
      offset = offsets[idx]

      for x = 8, 61 do
        map_transform_tile(map_id, first_row + offset, x, CTILE_TYPE_DUNGEON)
      end
    end

    add_guards_to_station(map_id, first_row-1, 8, 61)
    add_equipment_to_station(map_id, first_row+1, 8, 61)
  end
end

function init_carcassia_a2a(map_id)
  local first_row = 2
 
  init_sky_high_deals(map_id)
  init_first_row(map_id, first_row)
end

map_events.set_map_fn(map_id, init_carcassia_a2a)

