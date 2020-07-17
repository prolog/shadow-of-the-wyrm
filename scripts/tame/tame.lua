module(..., package.seeall)

tame_fns = {}

-- Set a tame function for a particular creature
function set_tame_fn(creature_base_id, fn)
  tame_fns[creature_base_id] = fn
end

function tame(creature_id, creature_base_id, taming_creature_id, map_id)
  local tame_fn = tame_fns[creature_base_id]

  if tame_fn ~= nil then
    tame_fn(creature_id, taming_creature_id, map_id)
  else
    tame_fn = tame_fns[creature_id]

    if tame_fn ~= nil then
      tame_fn(creature_id, taming_creature_id, map_id)
      tame_fns[creature_id] = nil
    else
      log(CLOG_ERROR, "Could not call tame function for creature_id " .. creature_id)
    end
  end
end

