require('areas')
local eka = Area:new(5, 49)

eka:set_custom_map_id("eka")
eka:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_EKA")

-- TODO: Make the location of the prison randomized.

eka:insert()
