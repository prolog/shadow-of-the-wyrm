require('carcassia_common')
require('constants')
require('fn')
require('map_events')

local map_id = "carcassia_b2"
local population = {"layperson", "devotee", "cleric", "follower", "apostle", "pilgrim", "carcassian_guard", "noble", "commoner", "thief", "urchin", "tradesman", "merchant", "traveller", "drunk"}

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
  if carcassia_garden_type == nil then
    -- See ReligiousCommercialSectorGenerator.hpp
    carcassia_garden_type = RNG_range(0, 1)
  end

  -- Always a shop across from the Fellowship
  generate_city_feature(map_id, 1, 3, 5, 16, CCITY_SECTOR_RELIGIOUS_COMMERCIAL, 3)

  -- A shrine below the shop.
  generate_city_feature(map_id, 7, 3, 11, 16, CCITY_SECTOR_RELIGIOUS_COMMERCIAL, 4)

  -- Wildflowers or rocks in front of the palace.
  local gt = carcassia_garden_type
  generate_city_feature(map_id, 13, 22, 18, 39, CCITY_SECTOR_RELIGIOUS_COMMERCIAL, gt)
  generate_city_feature(map_id, 13, 0, 18, 18, CCITY_SECTOR_RELIGIOUS_COMMERCIAL, gt)

  -- Always rocks alongside the palace.
  generate_city_feature(map_id, 13, 75, 17, 76, CCITY_SECTOR_RELIGIOUS_COMMERCIAL, 0)
end

local function init_carcassia_b2(map_id)
  setup_properties(map_id)
  setup_vault(map_id)
  setup_dynamic_content(map_id)
  carcassia_common.setup_population(map_id, {0,1}, {18, 37}, population)
end

map_events.set_map_fn(map_id, init_carcassia_b2)

