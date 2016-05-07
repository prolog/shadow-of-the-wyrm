require('decide')

goblin_traps = {"arrow_trap", "rock_trap", "crossbow_trap", 
                "flash_trap", "poison_dart_trap", "blackwater_trap"}

local function set_goblin_trap(creature_id)
  local creature_ids = {get_nearby_hostile_creatures(creature_id)}
  local trap_triggered = false

  -- For each nearby creature, see if it passes a Detection check.
  -- If any creatures pass their detection check, the trap should be
  -- generated as "seen"; otherwise, it will be hidden.
  for k,v in pairs(creature_ids) do
    if check_skill(v, 12) == true then
      trap_triggered = true
      break
    end
  end

  -- Now we've determined whether the trap is properly hidden or not.
  -- Set the trap appropriately on the trapper's square.
  local y, x = get_creature_yx(creature_id)
  local trap_id = goblin_traps[RNG_range(1, table.getn(goblin_traps))]

  set_trap(y, x, trap_triggered, trap_id)

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

