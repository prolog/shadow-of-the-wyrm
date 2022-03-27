require('create')

local function create_cat(creature_id, map_id)
  -- Cats can be brown, grey, black, or white.
  local cat_colours = {3, 7, 8, 15}
  local colour = cat_colours[RNG_range(1, #cat_colours)]

  set_creature_colour(creature_id, colour, map_id)
end

local cat_fn = create_cat
create.set_create_fn("cat", cat_fn)

