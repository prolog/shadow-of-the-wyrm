require('custom_map')

-- The base of the cloudspire is littered with very useful items to help
-- the player in the overwhelmingly unfair battle ahead.
--
-- These items are laid out in a checkerboard pattern.
function init_telari_base(map_id)
  local height, width = map_get_dimensions(map_id)
  local consumables = {"gain_attributes_potion"}

  for row = 0, height do
    for col = 0, width do
      if (row + col) % 2 == 0 then
        local tile_details = map_get_tile(map_id, row, col)

        -- Also to check: is this a floor tile?
        if tile_details ~= nil then
          -- ...
        end
      end
    end
  end
end

custom_map.set_map_fn("telari_base", init_telari_base)

