require('constants')
require('areas')

-- Figure out the general central area in which Carcassia can appear
local rows, cols = get_map_dimensions(WORLD_MAP_ID)
local y_off = rows / 3
local x_off = cols / 3

-- Get all the field tile coordinates in that range.
local field_tiles = 0
local potential_spots = get_coords_with_tile_type_in_range(WORLD_MAP_ID, 0 + y_off, 0 + x_off, rows - y_off, cols - y_off, field_tiles)

-- If nothing was returned, broaden the parameters so Carcassia can appear
-- anywhere.
local num_spots = table.getn(potential_spots)
if num_spots == 0 then
  -- Empire was founded somewhere funny this time!
  potential_spots = get_coords_with_tile_type_in_range(WORLD_MAP_ID, 0, 0, rows - 1, cols - 1, field_tiles)
end

-- Make sure we pick a spot without a custom map ID.  Don't overwrite
-- any of the predefined areas!
local c_coords

for i = 1, 10 do
  c_coords = potential_spots[RNG_range(1, table.getn(potential_spots))]
  local map_id = get_custom_map_id(WORLD_MAP_ID, c_coords[1], c_coords[2])

  if s == "" then
    break
  end
end

if c_coords ~= nil then
  log(CLOG_DEBUG, "Carcassia location: " .. c_coords[1] .. "," .. c_coords[2])

  -- Now that a tile has been selected, add Carcassia to the world map.
  local carcassia = Area:new(c_coords[1], c_coords[2])

  -- Set up the city tile appropriately.
  -- JCD FIXME uncomment when release-ready.
  carcassia:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CARCASSIA")
  carcassia:set_additional_property("TILE_PROPERTY_SETTLEMENT_TYPE", 4)

  -- carcassia:insert()
end

