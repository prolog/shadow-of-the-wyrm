require('attack')

-- Steal ivory off the attacked creature, and then vanish in a puff
-- of smoke.
local function steal(attacker_id, attacked_id)
  -- Steal some amount of currency off the creature, and transfer
  -- it to the attacker.

  -- Vanish!
end

local steal_fn = steal

-- Set up thievery for any creatures that require it.
attack.set_attack_fn("thief", steal_fn)
attack.set_attack_fn("snakeling_thief", steal_fn)

