require('areas')

local ae_id = "atuaelar"

local stonewall = Area:new(89, 14)
stonewall:set_custom_map_id("stonewall")
stonewall:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_STONEWALL")

local atua_elar = Area:new(92, 17)
atua_elar:set_custom_map_id(ae_id)
atua_elar:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_ATUA_ELAR")

stonewall:insert()
atua_elar:insert()

-- Shop details
local shop_id = "calathar_shop"
local shopkeeper_id = get_creature_id(13, 68, ae_id)
set_creature_name(shopkeeper_id, "Calathar", ae_id)
set_shop_shopkeeper_id(shop_id, shopkeeper_id, ae_id)
repop_shop(shop_id, ae_id)

