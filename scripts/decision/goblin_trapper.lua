require('decide')

local function set_goblin_trap(creature_id)
  local creature_ids = {get_nearby_hostile_creatures(creature_id)}
  local trap_hidden = true

  -- For each nearby creature, see if it passes a Detection check.
  -- If any creatures pass their detection check, the trap should be
  -- generated as "seen"; otherwise, it will be hidden.
  for k,v in pairs(creature_ids) do
    if check_skill(v, 12) == true then
      trap_hidden = false
      break
    end
  end

  -- Now we've determined whether the trap is properly hidden or not.
  -- Set the trap appropriately on the trapper's square.
  -- ...

  local action_cost = 10
  return action_cost
end

-- Goblin trappers can set traps, potentially - this is based on an
-- internal counter that determines "how many traps" they have left.
local function gt_decision_fn(creature_id)
  local set_trap_fn = set_goblin_trap
  
  local decision_fns = {set_trap_fn}
  return decision_fns
end

local gt_fn = gt_decision_fn

decide.set_decision_fn("goblin_trapper", gt_fn)

