require('constants')
require('fn')
require('map_events')

local map_id = "carcassia_b2"

local function setup_properties(map_id)
  map_set_tile_property(map_id, 18, 76, "MAP_PROPERTIES_INITIAL_ITEMS", "smite_spellbook")
end

local function setup_vault(map_id)
  local trap_squares = {{10,55},{11,54},{11,55},{11,56},{12,55}}

  for i, val in ipairs(trap_squares) do
    set_trap(val[1], val[2], false, "monster_trap", map_id)
  end

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

local function setup_dynamic_content(map_id)
  generate_city_feature(map_id, 13, 22, 18, 39, CCITY_SECTOR_RELIGIOUS_COMMERCIAL, 1)
  generate_city_feature(map_id, 13, 0, 18, 18, CCITY_SECTOR_RELIGIOUS_COMMERCIAL, 1)
end

local function init_carcassia_b2(map_id)
  setup_properties(map_id)
  setup_vault(map_id)
  setup_dynamic_content(map_id)
end

map_events.set_map_fn(map_id, init_carcassia_b2)

