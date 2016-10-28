require('constants')
require('areas')

local rows, cols = get_map_dimensions(OVERWORLD_MAP_ID)
local cy, cx = 0, 0 -- FIXME
local carcassia = Area:new(cy, cx)

-- Set up the city tile appropriately.
carcassia:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CARCASSIA")

carcassia:insert()
