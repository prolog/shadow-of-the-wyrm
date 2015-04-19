require('decide')
require('actions')

-- Thieves scavenge money off the ground.
local function thief_decision_fn(creature_id)
  log(CLOG_ERROR, "Here")
  local take_currency_fn = actions.take_currency
  log(CLOG_ERROR, "Here2")
  local decision_fns = {take_currency_fn}
  log(CLOG_ERROR, "Here3")
  return decision_fns
end

local thief_fn = thief_decision_fn

decide.set_decision_fn("thief", thief_fn)
decide.set_decision_fn("snakeling_thief", thief_fn)

