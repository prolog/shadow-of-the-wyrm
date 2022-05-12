require('areas')

local stoneheim_id = "stoneheim"
local creature = require('creature')
local creature_list = {{"avernal_bat", 25, 35}, {"mist_wraith", 10, 20}}

local creatures_csv = creature.to_csv(creature_list)

local world_shrine = Area:new(9, 10)
world_shrine:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_WORLD_SHRINE")
world_shrine:set_tile_subtype(21) -- always on a forest
world_shrine:set_additional_properties({["MAP_PROPERTIES_RELIC_ID"] = "heart_world", ["MAP_PROPERTIES_CREATURE_IDS"] = "dragon,war_mammoth,skywing,golgothan,shrine_hag,titan", ["MAP_PROPERTIES_IGNORE_CREATURE_LVL_CHECKS"] = "1", ["MAP_PROPERTIES_DIVINE_FORBIDDEN"] = "1"})

local wyrmeswraec = Area:new(6, 9)
wyrmeswraec:set_custom_map_id("wyrmeswraec")
wyrmeswraec:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_WYRMESWRAEC")

local caldera = Area:new(6, 18)
caldera:set_custom_map_id("caldera")
caldera:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_CALDERA")
caldera:set_additional_properties({["MAP_PROPERTIES_INITIAL_CREATURES"] = creatures_csv})

local stoneheim = Area:new(9, 19)
stoneheim:set_custom_map_id(stoneheim_id)
stoneheim:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_STONEHEIM")

world_shrine:insert()
wyrmeswraec:insert()
caldera:insert()
stoneheim:insert()

local shop_id = "hjalmar_shop"
local shopkeeper_id = get_creature_id(8, 71, stoneheim_id)
set_creature_name(shopkeeper_id, "Hjalmar", stoneheim_id)
set_shop_shopkeeper_id(shop_id, shopkeeper_id, stoneheim_id)
repop_shop(shop_id, stoneheim_id)

