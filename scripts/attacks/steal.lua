require('attack')

-- Steal ivory off the attacked creature, and then vanish in a puff
-- of smoke.
local function steal(attacker_id, attacked_id)
  -- Steal some amount of currency off the creature, and transfer
  -- it to the attacker.

  -- Add a message if the attacked creature is the player.
  add_message_for_creature(attacked_id, "STEAL_CURRENCY_MESSAGE")
  add_message_for_creature(attacked_id, "MONSTER_VANISHES_MESSAGE", {get_creature_description(attacked_id, attacker_id)})

  -- Vanish!
  teleport(attacker_id)
end

local steal_fn = steal

-- Set up thievery for any creatures that require it.
attack.set_attack_fn("thief", steal_fn)
attack.set_attack_fn("snakeling_thief", steal_fn)

