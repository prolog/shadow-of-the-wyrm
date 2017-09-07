require('constants')
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
  local deity_details = {{"celeste", {"crystalline_being", "seraph_highest_heavenly_order", "gabar_clutching_first_holy_book"}},
                         {"aurelion", {"knight_exemplar", "paragon_twenty_virtues", "trio_shining_silver_dragons"}},
                         {"the_lady", {"howling_fury_first_love_lost", "luminous_angel", "saint_who_moves_in_perfect_grace"}},
                         {"vedere", {"pulsating_mass_primordial_ooze", "cloud_murderous_flesh_eating_scarabs", "thunderbird_low_steppes"}},
                         {"voros", {"hundred_headed_hydra", "drakkhar_carrying_massive_flaming_sword", "early_dragon_first_age"}},
                         {"the_trickster", {"eddic_crone", "murder_thousand_crows", "wraith_wan_dying_light"}},
                         {"shiver", {"blood_angel_white_queen", "nether_hound", "ancient_shade"}},
                         {"urgoth", {"black_ogre", "cylonic_beast", "dark_rider_coming_horde"}}}

  local deity_idx = RNG_range(1, table.getn(deity_details))
  local deity_and_followers = deity_details[deity_idx]
  local cosmos_creatures = {deity_details[1]}
  local followers = deity_details[2]
  local generation_attempts = 500

  -- Add the deity, as well as 6d3 followers.

  -- Assume the player will be generated at 0,0 like on general terrain
  -- maps where an exit isn't involved, and use 1, n-1 for the rows and
  -- cols.
  for i = 1, RNG_dice(6, 3) do
    table.insert(cosmos_creatures, followers[RNG_range(1, #followers)])
  end

  -- Get a submap of the cosmos to generate on.
  -- This'll be needed in subsequent death scripts, so should be put
  -- somewhere common.
  local r, c = map_get_dimensions(map_id)
  local subrow_start, subcol_start = r/4, c/2
  local y1 = RNG_range(1, r-subrow_start-1)
  local y2 = y1 + subrow_start
  local x1 = RNG_range(1, c-subcol_start-1)
  local x2 = x2 + subcol_start

  local avail_coords = map_get_available_creature_coords(map_id, y1, y2, x1, x2)
  local rnd_indices = shuffle(numeric_array(1, #cosmos_creatures))

  for i = 1, #rnd_indices do
    local rnd_idx = rnd_indices[i]
    local c = avail_coords[rnd_idx]

    -- add_creature_to_map(...)
  end
end

map_events.set_map_fn(cosmos_map_id, init_cosmos)

