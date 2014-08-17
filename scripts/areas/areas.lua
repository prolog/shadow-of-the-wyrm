-- Areas module - used for specifying areas, which can then be inserted
-- into a given map (typically the world map).
Area = {}
Area.__index = Area

function Area:new(row, col)
  local obj = {}
  setmetatable(obj, self)
  
  -- Set the row and column for this area.
  obj.row = row
  obj.col = col

  -- Set the additional properties to an empty table.
  obj.additional_properties = {}

  -- Assume the area is placed on the world map unless we're told
  -- otherwise.
  obj.map_id = "overworld"

  return obj
end

-- Set a custom map ID - used to link tiles to the custom maps found in
-- data/maps.
function Area:set_custom_map_id(id)
  self.cust_map_id = id
end

-- Set permanence as an additional property.  If the tile does not refer
-- to a custom map, but instead generates based on a FieldGenerator or
-- whatever, this will ensure that the permanence flag is turned on at
-- the end.
function Area:set_permanence(perm)
  self.permanence = perm
end

-- Set an extra description SID, displayed on the world map when the
-- player walks over/looks at the tile.
function Area:set_extra_description_sid(sid)
  self.edesc_sid = sid
end

-- Set a particular property on the tile.
function Area:set_additional_property(property, value)
  map_set_additional_property(self.map_id, self.row, self.col, property, value)
end

-- Set the additional properties.
function Area:set_additional_properties(addl_properties)
  self.additional_properties = addl_properties
end

-- Set the area details on the specified map
function Area:insert()
  -- If a custom map ID has been specified, set that.
  if (self.cust_map_id ~= nil) then
    map_set_custom_map_id(self.map_id, self.row, self.col, self.cust_map_id)
  end

  -- If we need to override the permanence, do so.
  if (self.permanence ~= nil) then
    map_set_additional_property(self.map_id, self.row, self.col, "MAP_PROPERTIES_PERMANENCE", tostring(self.permanence))
  end

  -- Next, check to see if an extra description SID has been provided.
  -- If so, link that.
  if (self.edesc_sid ~= nil) then
    map_set_edesc(self.map_id, self.row, self.col, self.edesc_sid)
  end

  -- Finally, add any additional properties.
  for k,v in pairs(self.additional_properties) do
    map_set_additional_property(self.map_id, self.row, self.col, k, v)
  end
end

