module(..., package.seeall)

map_fns = {}

function set_map_fn(map_id, fn)
  map_fns[map_id] = fn
end

-- init_map gets called after a custom map is loaded from the XML,
-- assuming there's an associated script (most maps are static/basic and
-- don't require scripts).
function init_map(map_id)
  local map_fn = map_fns[map_id]

  if map_fn ~= nil then
    map_fn(map_id)
  else
    log(CLOG_ERROR, "Could not call map function for map ID " .. map_id)
  end
end

