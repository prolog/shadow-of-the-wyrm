require('areas')

local stonewall = Area:new(89, 14)
stonewall:set_custom_map_id("stonewall")
stonewall:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_STONEWALL")

local atua_elar = Area:new(92, 17)
atua_elar:set_custom_map_id("atuaelar")
atua_elar:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ATUA_ELAR")

stonewall:insert()
atua_elar:insert()

