require('constants')
require('map_events')

local cosmos_map_id = args[MAP_ID]

-- Initializing the cosmos is done by picking a deity, and spawning it
-- along with a number of its followers.  These are given action speeds
-- greater than the player's to ensure that the player always gets to act
-- first.
-- 
-- Sceadugenga is excluded from the initial spawn.  He is always the last 
-- to generate.
function init_cosmos(map_id)
end

map_events.set_map_fn(cosmos_map_id, init_cosmos)

