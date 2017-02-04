module(..., package.seeall)

-- Check an array to see if it contains a particular value
function contains(array, value)
  for k,v in pairs(array) do
    if v == value then
      return true
    end
  end

  return false
end

