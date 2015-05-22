require('items')

-- When a clay pot smashes and this script runs, an item is created.
-- Either an ivory piece, or in much rarer cases, something more useful.
local function pot_smash(item_original_id, creature_original_id, row, col)
  -- Add a message about the pot smashing.
  add_message_for_creature(creature_original_id, "AMMUNITION_DESTRUCTION_SMASH")

  -- Create the item on the tile.
  local base_id = ""
  local quantity = 1
  if RNG_percent_chance(1) then
    base_id = "ether_potion"
  elseif RNG_percent_chance(2) then
    base_id = "healing_potion"
  else
    base_id = "_currency"
    quantity = RNG_range(2,3)
  end

  add_object_to_tile(base_id, row, col, quantity)
end

-- Set up the clay pot functions.
local pot_fn = pot_smash
items.set_item_fn("clay_pot", "ITEM_EVENT_AMMO_DESTRUCT", pot_fn)

