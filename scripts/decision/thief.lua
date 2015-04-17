require('attack')
require('take_currency')

-- Thieves scavenge money off the ground.
local function thief_decision_fn(creature_id)
  local take_currency_fn = take_currency
  local decision_fns = {take_currency_fn}
  return decision_fns
end

local thief_fn = thief_decision_fn

set_decision_fn("thief", thief_fn)
set_decision_fn("snakeling_thief", thief_fn)
