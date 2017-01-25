require('areas')

local last_rock = Area:new(99, 81)
last_rock:set_custom_map_id("whalings_end")
last_rock:set_extra_description_sid("TILE_EXTRA_DESCRIPTION_WHALINGS_END")

last_rock:insert()

local map_id = "whalings_end"

-- Set up some details for the shopkeepers.  First element is the creature
-- ID.  Second item is an array containing the types of items they stock.
--
-- Davos stocks weapons, armour, and food; Itzchak sells magical items.
local sk_details = {{id = get_creature_id(7, 22, map_id),
                     name = "Davos",
                     shop_id = "davos_shop"}, 
                    {id = get_creature_id(7, 55, map_id), 
                     name = "Itzchak",
                     shop_id = "itzchak_shop"}}

for i = 1, #sk_details do
  set_creature_name(sk_details[i].id, sk_details[i].name, map_id)
  set_shop_shopkeeper_id(sk_details[i].shop_id, sk_details[i].id, map_id)

  -- repopulate the shop...
end

