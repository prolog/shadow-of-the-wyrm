require('constants')
require('areas')

-- Set up the seat of the empire.
local carcassia = Area:new(39, 50)

-- Set up the city tile appropriately.
carcassia:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CARCASSIA")
carcassia:insert()

