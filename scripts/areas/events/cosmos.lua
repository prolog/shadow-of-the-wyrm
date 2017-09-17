require('constants')
require('fn')
require('map_events')

local cosmos_map_id = args[MAP_ID]

-- Initializing the cosmos is done by picking a deity, and spawning it
-- along with a number of its followers.  These are given action speeds
-- greater than the player's to ensure that the player always gets to act
-- first.
-- 
-- Sceadugenga is excluded from the initial spawn.  He is always the last 
-- to generate.
function init_cosmos(map_id)
  local deity_details = {{"celeste", {"crystalline_being", 
                                      "seraph_highest_heavenly_order", 
                                      "gabar_clutching_first_holy_book"}},
                         {"aurelion", {"knight_exemplar", 
                                       "paragon_twenty_virtues", 
                                       "trio_shining_silver_dragons"}},
                         {"the_lady", {"howling_fury_first_love_lost", 
                                       "luminous_angel", 
                                       "saint_who_moves_in_perfect_grace"}},
                         {"vedere", {"pulsating_mass_primordial_ooze", 
                                     "cloud_murderous_flesh_eating_scarabs", 
                                     "thunderbird_low_steppes"}},
                         {"voros", {"hundred_headed_hydra", 
                                    "drakkhar_carrying_massive_flaming_sword", 
                                    "early_dragon_first_age"}},
                         {"the_trickster", {"eddic_crone", 
                                            "murder_thousand_crows", 
                                            "wraith_wan_dying_light"}},
                         {"shiver", {"blood_angel_white_queen", 
                                     "nether_hound", 
                                     "ancient_shade"}},
                         {"urgoth", {"black_ogre", 
                                     "cylonic_beast", 
                                     "dark_rider_coming_horde"}}}

  local deity_idx = RNG_range(1, table.getn(deity_details))
  local deity_and_followers = deity_details[deity_idx]

  local cosmos_creatures = {deity_and_followers[1]}
  local followers = deity_and_followers[2]

  -- Add the deity, as well as followers.  Each tile in the rift will
  -- get a divine creature.

  -- Assume the player will be generated at 0,0 like on general terrain
  -- maps where an exit isn't involved, and use 1, n-1 for the rows and
  -- cols.
  for i = 1, 8 do
    local rnd_idx = RNG_range(1, #followers)
    table.insert(cosmos_creatures, followers[rnd_idx])
  end

  -- Generate the rift and the exclusionary area around the center
  -- of the map.
  local r, c = map_get_dimensions(map_id)
  local rift_y, rift_x = r / 2, c / 2
  local cnt = 1
  
  cosmos_creatures = fn.shuffle(cosmos_creatures)

  -- Generate creatures in the rift area
  for ry = rift_y - 1, rift_y + 1 do
    for rx = rift_x - 1, rift_x + 1 do
      add_basic_feature_to_map("_rift", ry, rx, map_id)
      
      -- Ensure that the player can't enter the rift.  Only the divine
      -- may pass.
      map_set_additional_property(map_id, ry, rx, "TILE_PROPERTY_ALLOWED_RACES", "_divine")

      add_creature_to_map(cosmos_creatures[cnt], ry, rx, map_id)
      cnt = cnt + 1
    end
  end

  -- Generate lesser divine beings throughout the level.
  -- ...
end

map_events.set_map_fn(cosmos_map_id, init_cosmos)

