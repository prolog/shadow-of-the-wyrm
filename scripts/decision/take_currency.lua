-- Attempt to scavenge any currency on the current tile.  Returns the
-- action cost if this was done, 0 otherwise.
local function take_currency(creature_id)
  local action_cost = 0
  local currency_id = "_currency"

  if creature_tile_has_item(creature_id, currency_id) then
    -- Pick up the first pile of ivory on the tile.
    action_cost = pick_up_item(creature_id, currency_id)
  end

  return action_cost
end

