require('custom_map')

local map_id = "telari_base"

-- The base of the cloudspire is littered with very useful items to help
-- the player in the overwhelmingly unfair battle ahead.
function init_telari_base(map_id)
  local height, width = map_get_dimensions(map_id)
  local consumables = {"gain_attributes_potion", "restorative_potion", 
                       "amut_potion", "speed_potion", "ether_potion",
                       "healing_potion", "teleport_wand", 
                       "dragon_breath_wand", "vorpal_bolt_wand", 
                       "enchanting_scroll"}

  for row = 0, height-1 do
    for col = 0, width-1 do
      if (row + col) % 2 == 0 and RNG_percent_chance(10) then
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

custom_map.set_map_fn(map_id, init_telari_base)

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

