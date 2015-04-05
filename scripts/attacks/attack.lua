module(..., package.seeall)

-- Per-creature post-successful-attack functions.
attack_fns = {}

-- Set a creature's attack function
function set_attack_fn(original_id, fn)
  attack_fns[original_id] = fn
end

-- "attack" has a chance of being called after a successful attack.
-- It allows things like nethack-style leprechaun money theft, etc.
function attack(original_id, attacker_id, attacked_id)
  local attack_fn = attack_fns[original_id]

  if attack_fn ~= nil then
    attack_fn(attacker_id, attacked_id)
  else
    log(CLOG_ERROR, "Could not call attack function for base ID " .. original_id)
  end
end

