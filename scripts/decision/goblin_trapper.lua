require('decide')

local function set_goblin_trap(creature_id)
  -- JCD FIXME: Actual functionality goes here.
  local creature_id_csv = get_nearby_hostile_creatures(creature_id)

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

