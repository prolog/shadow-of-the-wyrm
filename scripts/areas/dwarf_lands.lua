require('areas')

local creature = require('creature')
local creature_list = {{"avernal_bat", 25, 35}, {"mist_wraith", 10, 20}}

local creatures_csv = creature.to_csv(creature_list)

local world_shrine = Area:new(9, 10)
world_shrine:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_WORLD_SHRINE")

local wyrmeswraec = Area:new(6, 9)
wyrmeswraec:set_custom_map_id("wyrmeswraec")
wyrmeswraec:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_WYRMESWRAEC")

local caldera = Area:new(6, 18)
caldera:set_custom_map_id("caldera")
caldera:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CALDERA")
caldera:set_additional_properties({["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_csv})

local stoneheim = Area:new(9, 19)
stoneheim:set_custom_map_id("stoneheim")
stoneheim:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_STONEHEIM")

world_shrine:insert()
wyrmeswraec:insert()
caldera:insert()
stoneheim:insert()

