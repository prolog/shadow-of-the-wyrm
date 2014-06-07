-- Common functions for working with creatures in the Lua code.
local creature = {}

-- Assumes that creature_details is an array, each element of which
-- contains three items: a creature id (string), a minimum number to
-- generate (number), and a maximum (number).  If the minimum is nil,
-- assume 1.  If the maximum is nil, assume it is the same as the
-- minimum.
function creature.to_csv(creature_details)
  local creature_csv = ""

  for i, details in ipairs(creature_details) do
    local creature_id = details[1]
    local min = details[2]
    local max = details[3]

    if (min == nil) then
      min = 1
    end

    if (max == nil) then
      max = min
    end

    if max >= min then
      local num = RNG_range(min, max)

      for j = 1, num do
        creature_csv = creature_csv .. creature_id .. ","
      end
    end
  end

  log(CLOG_DEBUG, "Creature CSV: " .. creature_csv)

  return creature_csv
end

return creature

