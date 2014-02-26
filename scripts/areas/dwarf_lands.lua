require('areas')

local wyrmeswraec = Area:new(6, 9)
wyrmeswraec:set_custom_map_id("wyrmeswraec")
wyrmeswraec:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_WYRMESWRAEC")

local stoneheim = Area:new(9, 19)
stoneheim:set_custom_map_id("stoneheim")
stoneheim:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_STONEHEIM")

wyrmeswraec:insert()
stoneheim:insert()

