module(..., package.seeall)

-- Per-creature item functions.
item_fns = {}

function create_table_key(base_item_id, item_event)
  local table_key = base_item_id .. "-" .. item_event
  return table_key
end

function set_item_fn(base_item_id, item_event, fn)
  local table_key = create_table_key(base_item_id, item_event)
  item_fns[table_key] = fn
end

-- item_event_fn has a chance of being called at particular times for
-- an object - e.g., after a piece of ammunition has been destroyed.
-- 
-- To the looked-up function, the row and column of the tile the item
-- is on is provided.
function item_event_fn(base_item_id, original_creature_id, item_event, item_row, item_col)
  local table_key = create_table_key(base_item_id, item_event)
  local item_fn = item_fns[table_key]

  if item_fn ~= nil then
    item_fn(base_item_id, original_creature_id, item_row, item_col)
  else
    log(CLOG_ERROR, "Could not call item function for event " .. item_event " and original ID " .. base_item_id .. " at coordinates (" .. row .. ", " .. col .. "), original_creature_id=" .. original_creature_id)
  end
end

