module(..., package.seeall)

-- Per-creature drop functions.  Called when an item is dropped.
drop_fns = {}

-- Set a creature's drop function
function set_drop_fn(original_id, fn)
  drop_fns[original_id] = fn
end

-- The "drop" function is called after each drop.  The engine will loop
-- through all the creatures in the dropping creature's FOV map, and
-- run the script.
function drop(dropping_creature_id, fov_creature_id, fov_creature_base_id, item_id, item_base_id, drop_y, drop_x)
  local drop_fn = drop_fns[fov_creature_base_id]

  if drop_fn ~= nil then
    drop_fn(dropping_creature_id, fov_creature_id, item_id, item_base_id, drop_y, drop_x)
  end
end
