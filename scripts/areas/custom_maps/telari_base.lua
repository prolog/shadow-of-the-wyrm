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

-- On the up staircase, set the "danger level fixed" property so that it
-- can propagate up the tower.
map_set_tile_property(map_id, 12, 40, "MAP_PROPERTIES_CREATURE_DANGER_LEVEL_FIXED", "1")

-- JCD FIXME: Set the tower peak details.
