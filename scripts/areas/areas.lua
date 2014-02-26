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
  obj.addl_props = {}

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

-- Set an extra description SID, displayed on the world map when the
-- player walks over/looks at the tile.
function Area:set_extra_description_sid(sid)
  self.edesc_sid = sid
end

-- Set the area details on the specified map
function Area:insert()
  -- If a custom map ID has been specified, set that.
  if (self.cust_map_id ~= nil) then
    map_set_custom_map_id(self.map_id, self.row, self.col, self.cust_map_id)
  end

  -- Next, check to see if an extra description SID has been provided.
  -- If so, link that.
  if (self.edesc_sid ~= nil) then
    map_set_edesc(self.map_id, self.row, self.col, self.edesc_sid)
  end

  -- Finally, add any additional properties.
  for k,v in pairs(self.addl_props) do
    map_set_addl_prop(self.map_id, self.row, self.col, k, v)
  end
end

