require('decide')

-- Comet jellyfish randomly change colours
local colours = {9,10,11,12,13,14}

-- Get the next colour for the jellyfish.
local function change_colour(creature_id)
  log(CLOG_DEBUG, "Changing colour for creature_id " .. creature_id)

  local cj_colour = get_creature_colour(creature_id)
  local next_colour = colours[RNG_range(1, table.getn(colours))]

  log(CLOG_DEBUG, "Changing colour from " .. cj_colour .. " to " .. next_colour)

  set_creature_colour(creature_id, next_colour)

  local action_cost = 1
  return action_cost
end

local function cj_decision_fn(creature_id)
  local change_colour_fn = change_colour
  
  local decision_fns = {change_colour_fn}
  return decision_fns
end

local cj_fn = cj_decision_fn

decide.set_decision_fn("comet_jellyfish", cj_fn)

