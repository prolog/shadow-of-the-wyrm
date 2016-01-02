module(..., package.seeall)

-- Per-creature death functions.
death_fns = {}

-- Set a death function for a particular creature
function set_death_fn(creature_base_id, fn)
  death_fns[creature_base_id] = fn
end

function die(creature_id, creature_base_id, attacking_creature_id)
  local death_fn = death_fns[creature_base_id]

  if death_fn ~= nil then
    death_fn(creature_id, attacking_creature_id)
  else
    log(CLOG_ERROR, "Could not call death function for creature_id " .. creature_id)
  end
end
