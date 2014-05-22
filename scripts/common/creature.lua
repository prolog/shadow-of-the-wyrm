-- Common functions for working with creatures in the Lua code.
local creature = {}

-- Assumes that creature_details is an array, each element of which
-- contains three items: a creature id (string), a minimum number to
-- generate (number), and a maximum (number).
function creature.to_csv(creature_details)
  local creature_csv = ""

  for i, details in ipairs(creature_details) do
    local creature_id = details[1]
    local min = details[2]
    local max = details[3]

    if max > min then
      local num = RNG_range(min, max)

      for j = 1, num do
        creature_csv = creature_csv .. creature_id

        if j ~= num and i ~= #creature_details then
          creature_csv = creature_csv .. ","
        end
      end
    end
  end

  return creature_csv
end

return creature

