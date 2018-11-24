require('fn')
module(..., package.seeall)

function setup_population(map_id, start_coord, end_coord, creature_ids)
  local area = fn.area(start_coord, end_coord)
  local num_creatures = RNG_range(area / 40, area / 20)

  for i = 1, num_creatures do
    local y = RNG_range(start_coord[1], end_coord[1])
    local x = RNG_range(start_coord[2], end_coord[2])
    local cr_id = creature_ids[RNG_range(1, #creature_ids)]

    add_creature_to_map(cr_id, y, x, map_id)
  end
end

