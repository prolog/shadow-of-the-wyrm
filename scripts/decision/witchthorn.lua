require('constants')
require('decide')

local function fire_thorns(creature_id)
  local creature_ids = {get_nearby_hostile_creatures(creature_id)}
  local thorns_fired = 0

  -- If there aren't any nearby hostile creatures, don't fire any thorns,
  -- and return an action cost value of 0.
  if next(creature_ids) == nil then
    return thorns_fired
  end

  for i, attacked_cr_id in ipairs(creature_ids) do
    add_fov_message(creature_id, attacked_cr_id, "WITCHTHORN_THORN_FIRED")
    
    -- Attack, dealing 1d3 DamageType::DAMAGE_TYPE_PIERCE (1) damage, 
    -- with piercing = true
    ranged_attack(creature_id, attacked_cr_id, RNG_range(1, 3), 1, true)
    thorns_fired = thorns_fired + 1
  end

  return thorns_fired
end

-- Witchthorns are totally immobile - generally bad for them.  But they
-- have a seemingly infinite supply of needle-like thorns to fire at
-- hostile creatures, so it's not all bad.
local function witchthorn_decision_fn(creature_id)
  local fire_thorns_fn = fire_thorns
  
  local decision_fns = {fire_thorns_fn}
  return decision_fns
end

local witchthorn_fn = witchthorn_decision_fn

decide.set_decision_fn("witchthorn", witchthorn_fn)

