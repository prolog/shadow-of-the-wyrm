require('carcassia_common')
require('constants')
require('map_events')

local map_id = "carcassia_a2a"
local walkway_features = {{CCLASS_ID_FIRE_PILLAR}, {CCLASS_ID_FOUNTAIN}}

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
  local rng_min = 6
  local rng_max = 12
  local rare_ammo = {EXPLODING_ARROW_ID, WINGED_JAVELIN_ID}
  for x = col_start, col_end do
    if RNG_percent_chance(60) then
      local ammo_id = ammo[RNG_range(1, #ammo)]

      if RNG_percent_chance(7) then
        ammo_id = rare_ammo[RNG_range(1, #rare_ammo)]
        rng_min = 4
        rng_max = 6
      end

      add_object_to_map(ammo_id, map_id, row, x, RNG_range(rng_min, rng_max))
    end
  end
end

local function add_walkway_features(map_id, row, col_start, col_end, ww_idx)
  local features = walkway_features[ww_idx]

  for x = col_start, col_end do
    if x % 6 == 0 then
      local feature_id = features[RNG_range(1, #features)]
      add_feature_to_map(row, x, feature_id, map_id)
    end
  end
end

local function init_north_walk(map_id, first_row)
  local guard_station = RNG_percent_chance(100)

  local start_x = 6
  for x = start_x, 61 do
    map_transform_tile(map_id, first_row, x, CTILE_TYPE_DUNGEON)
  end

  local offsets = {-1, 1}
  local feature_idx = RNG_range(1, #walkway_features)

  for idx = 1, #offsets do
    offset = offsets[idx]

    for x = 8, 61 do
      map_transform_tile(map_id, first_row + offset, x, CTILE_TYPE_DUNGEON)
    end

    if guard_station == true then
      if offset == -1 then
        add_guards_to_station(map_id, first_row+offset, 8, 61)
      else
        add_equipment_to_station(map_id, first_row+offset, 8, 61)
      end
    else
      add_walkway_features(map_id, first_row+offset, 8, 61, feature_idx)
    end
  end
end

local function init_southern_plaza_gaps(map_id, start_y, end_y, start_x, end_x)
  -- Small chance it's just a straight-up open plaza. Otherwise, it will
  -- have gaps/drops that if I'm being honest are only so it looks interesting
  -- when rendered on the map.
  local incr = RNG_range(1,2)

  if RNG_percent_chance(90) then
    for i = 0, 4, incr do
      local cur_sy = start_y + i
      local cur_ey = end_y - i
      local cur_sx = start_x + i
      local cur_ex = end_x - i

      -- Good chance of decorative corners
      if RNG_percent_chance(70) then
        corners = fn.make_corners(cur_sy, cur_ey, cur_sx, cur_ex)

        for k,v in pairs(corners) do
          -- Turn the corner into an air tile.
          map_transform_tile(map_id, v[1], v[2], CTILE_TYPE_AIR)
        end
      end
    end
  end
end

local function init_southern_plaza_features(map_id, start_y, end_y, start_x, end_x)
end

local function init_southern_plaza_creatures(map_id, start_y, end_y, start_x, end_x)
end

local function init_southern_plaza(map_id)
  local start_y = 5
  local end_y = 17
  local start_x = 10
  local end_x = 38
  
  init_southern_plaza_gaps(map_id, start_y, end_y, start_x, end_x)
  init_southern_plaza_features(map_id, start_y, end_y, start_x, end_x)
  init_southern_plaza_creatures(map_id, start_y, end_y, start_x, end_x)
end

function init_carcassia_a2a(map_id)
  local first_row = 2
 
  init_sky_high_deals(map_id)
  init_north_walk(map_id, first_row)
  init_southern_plaza(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_a2a)

