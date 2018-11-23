module(..., package.seeall)

function make_coordinates(r1, r2, c1, c2)
  local coords = {}
  for y = r1, r2 do
    for x = c1, c2 do
      table.insert(coords, {y, x})
    end
  end

  return coords
end

-- Check an array to see if it contains a particular value
function contains(array, value)
  for k,v in pairs(array) do
    if v == value then
      return true
    end
  end

  return false
end

-- Get the size of an associative table.
-- This function is called atable_size to discourage calling it for
-- arrays, where the Lua built-ins should suffice.
function atable_size(atable)
  local cnt = 0
  for k,v in pairs(atable) do
    cnt = cnt + 1
  end

  return cnt
end

-- Create an array of numbers, starting at i, to n, inclusive.
--
-- Example usage: numeric_array(1, 3) -> {1,2,3}
--                numeric_array(-3, 1) -> {-3,-2,-1,0,1}
function numeric_array(i, n)
  local arr = {}

  if n > i then
    for num = i, n do
      table.insert(arr, num)
    end
  end

  return arr
end

-- Fisher-Yates shuffle, in place
function shuffle(t)
  local sz = #t
  for i = 1, sz-2 do
    local rnd = RNG_range(1, sz)
    t[i], t[rnd] = t[rnd], t[i]
  end

  return t
end

function stringify_array(t)
  local s_a = {}

  for i = 1, #t do
    table.insert(s_a, tostring(t[i]))
  end

  return s_a
end

function array_to_csv(t)
  local csv = ""
  for i = 1, #t do
    csv = csv .. t[i]

    if i < #t then
      csv = csv .. ","
    end
  end

  return csv
end

function area(c1, c2)
  return ((c2[1] - c1[1]) * (c2[2] - c1[2]))
end

