require('map_events')

local map_id = "telari_base"

function populate_fountains(map_id, height, width)
  local centre_y = height / 2
  local centre_x = width / 2
  local feature_id = CCLASS_ID_FOUNTAIN
  
  for y = 0, height-1, 2 do
    for x = centre_x - 1, centre_x + 1, 2 do
      local tile_details = map_get_tile(map_id, y, x)

      if tile_details ~= nil then
        local tile_type = tile_details["tile_type"]
        
        if tile_type == CTILE_TYPE_DUNGEON then
          add_feature_to_map(feature_id, y, x, map_id) 
        end
      end
    end
  end

  for x = 0, width-1, 3 do
    local tile_details = map_get_tile(map_id, centre_y, x)

    if tile_details ~= nil then
        local tile_type = tile_details["tile_type"]
        
        if tile_type == CTILE_TYPE_DUNGEON then
          add_feature_to_map(feature_id, centre_y, x, map_id) 
        end
    end
  end
end

function populate_consumables(map_id, height, width)
  local consumables = {"gain_attributes_potion", "restorative_potion", 
                       "amut_potion", "speed_potion", "ether_potion",
                       "healing_potion", "teleport_wand", 
                       "dragon_breath_wand", "vorpal_bolt_wand", 
                       "enchanting_scroll"}

  for row = 0, height-1 do
    for col = 0, width-1 do
      if (row + col) % 3 == 0 and RNG_percent_chance(10) then
        local tile_details = map_get_tile(map_id, row, col)
        local tile_type = tile_details["tile_type"]

        if tile_type == nil then
          log(CLOG_ERROR, "Tile nil at " .. tostring(row) .. "," .. tostring(col))
        end

        if tile_details ~= nil and tile_type == CTILE_TYPE_DUNGEON then
          local item_id = consumables[RNG_range(1, #consumables)]
          add_object_to_map(item_id, map_id, row, col)
        end
      end
    end
  end
end

-- The base of the cloudspire is littered with very useful items to help
-- the player in the overwhelmingly unfair battle ahead.
function init_telari_base(map_id)
  local height, width = map_get_dimensions(map_id)

  populate_fountains(map_id, height, width)
  populate_consumables(map_id, height, width)
end

map_events.set_map_fn(map_id, init_telari_base)

-- Generate random floating tower levels.
map_set_tile_subtype(map_id, 12, 40, CTILE_TYPE_FLOATING_TOWER)

local properties = {{"MAP_PROPERTIES_CREATURE_DANGER_LEVEL_FIXED", "1"},
                    {"MAP_PROPERTIES_CREATURE_DANGER_LEVEL_FIXED_RECURSIVE", "1"},
                    {"-75_DEPTH_MAP_PROPERTIES_SHIMMER_COLOURS", "9,1,11"},
                    {"-80_DEPTH_MAP_PROPERTIES_SHIMMER_COLOURS", "12,4,14"},
                    {"-85_DEPTH_MAP_PROPERTIES_SHIMMER_COLOURS", "3,8,11"},
                    {"-90_DEPTH_MAP_PROPERTIES_SHIMMER_COLOURS", "15,7,4"},
                    {"-95_CUSTOM_MAP_ID", "telari_top"},
                    {"TILE_PROPERTIES_DEPTH_INCREMENT", "-5"},
                    {"MAP_PROPERTIES_CANNOT_PRAY", "1"},
                    {"MAP_PROPERTIES_CANNOT_PRAY_RECURSIVE", "1"},
                    {"MAP_PROPERTIES_CANNOT_DIG", "1"},
                    {"MAP_PROPERTIES_CANNOT_DIG_RECURSIVE", "1"}}

for i,p_pair in ipairs(properties) do
  map_set_tile_property(map_id, 12, 40, p_pair[1], p_pair[2])
end

