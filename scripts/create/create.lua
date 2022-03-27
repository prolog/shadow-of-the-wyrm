module(..., package.seeall)

-- Per-creature creation functions.
create_fns = {}

-- Set a death function for a particular creature
function set_create_fn(creature_base_id, fn)
  create_fns[creature_base_id] = fn
end

function create(creature_id, creature_base_id, map_id)
  local create_fn = create_fns[creature_base_id]

  if create_fn ~= nil then
    create_fn(creature_id, map_id)
  else
    log(CLOG_ERROR, "Could not call create function for creature_id " .. creature_id)
  end
end

