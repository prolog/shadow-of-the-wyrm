require('constants')
require('fn')

-- get_treasure_items returns a CSV of items suitable for inclusion in
-- a treasure trove.
function get_treasure_items()
  local rings = {RING_FLAME_ID, RING_ICE_ID, RING_ACID_ID, RING_HOLINESS_ID}
  local ring_id = rings[RNG_range(1, #rings)]

  log(CLOG_ERROR, "1")

  local wands = {DRAGON_BREATH_WAND_ID, ARCANE_WAND_ID, FLAME_WAND_ID, LIGHTNING_WAND_ID, TELEPORT_WAND_ID}
  local wand_id = wands[RNG_range(1, #wands)]

  log(CLOG_ERROR, "2")

  local items = {GOLDEN_APPLE_ID, SILVER_APPLE_ID, SILVERWEED_ID, STONEFLOWER_ID, GAIN_ATTRIBUTES_POTION_ID, ENCHANTING_SCROLL_ID, ring_id, wand_id, SHADOW_BOMB_ID, FIRE_BOMB_ID}

  return fn.array_to_csv(items)
end

