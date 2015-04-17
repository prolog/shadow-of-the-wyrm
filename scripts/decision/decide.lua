module(..., package.seeall)

decision_fns = {}

-- Set a per-creature decision function
function set_decision_fn(original_id, fn)
  decision_fns[original_id] = fn
end

-- Check to see if a creature-defined decision function exists.
-- If it does, run it, and base the return value on the result.
function decide(original_id, creature_id)
  local result = false
  local creature_decision_fn = decision_fns[original_id]

  if (creature_decision_fn ~= nil) then
    local decision_fns = creature_decision_fn(creature_id)

    -- Each creature decision function returns an array of decision
    -- functions to be checked in order, stopping if any returns true.
    for i, d_fn in ipairs(decision_fns) do
      local return_val = d_fn(creature_id)

      -- If the current decision function fired off successfully, stop
      -- iterating over the list of functions, and return true.
      if return_val == true then
        result = true
        break
      end
    end
  else
    log(CLOG_ERROR, "nil found for decision function for creature with base ID: " .. original_id)
  end

  return result
end

