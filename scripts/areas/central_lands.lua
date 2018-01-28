require('constants')
require('areas')

-- Set up the seat of the empire.
local carcassia = Area:new(47, 53)

-- Set up the city tile appropriately.
carcassia:set_custom_map_id("carcassia_a1")
carcassia:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CARCASSIA")
carcassia:insert()

