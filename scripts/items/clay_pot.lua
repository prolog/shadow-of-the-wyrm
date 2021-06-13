require('constants')
require('fn')
require('items')

-- When a clay pot smashes and this script runs, an item is created.
-- Either an ivory piece, or in much rarer cases, something more useful.
local function pot_smash(item_original_id, props, creature_original_id, row, col)
  -- Add a message about the pot smashing.
  add_message_for_creature(creature_original_id, "AMMUNITION_DESTRUCTION_SMASH")

  local props_t = fn.props_to_table(props)
  local suppress_val = props_t[ITEM_PROPERTIES_SUPPRESS_ITEM_GENERATION_ON_DESTRUCTION]

  log(CLOG_ERROR, "props: " .. props)
  log(CLOG_ERROR, "size: " .. tostring(props_t))

  for key,val in pairs(props_t) do
    log(CLOG_ERROR, key .. val)
  end

  if suppress_val ~= "1" then
    -- Create the item on the tile.
    local base_id = ""
    local quantity = 1
    if RNG_percent_chance(1) then
      base_id = "_ether_potion"
    elseif RNG_percent_chance(2) then
      base_id = "_healing_potion"
    elseif RNG_percent_chance(2) then
      base_id = "_unstoning_potion"
    else
      base_id = CURRENCY_ID
      quantity = RNG_range(2,3)
    end

    log(CLOG_ERROR, "Adding item: " .. base_id)
    add_object_to_tile(base_id, row, col, quantity)
  end
end

-- Set up the clay pot functions.
local pot_fn = pot_smash
items.set_item_fn("_clay_pot", "ITEM_EVENT_AMMO_DESTRUCT", pot_fn)

