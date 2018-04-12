require('constants')
require('fn')
require('map_events')

local map_id = "carcassia_b2"

local function setup_vault(map_id)
  set_trap(10, 55, false, monster_trap, map_id)

  for row = 6,10 do
    for col = 52,58 do
      map_set_tile_property(map_id, row, col, "TILE_PROPERTY_CANNOT_DIG", "1")
      local tile_details = map_get_tile(map_id, row, col)
      
      if tile_details ~= nil then
        local tile_type = tile_details["tile_type"]

        if tile_type == CTILE_TYPE_DUNGEON then
          local amount = RNG_range(10, 30)
          add_object_to_map(CURRENCY_ID, map_id, row, col, amount)
        end
      end
    end
  end
end

local function init_carcassia_b2(map_id)
  setup_vault(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_b2)

