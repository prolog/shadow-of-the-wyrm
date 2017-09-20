module("cosmos_common", package.seeall)

-- Calculate the centre of a rift, which is always the centre of the
-- map's coordinates.
function get_rift_yx(r, c)
  return r / 2, c / 2
end

-- Given an array that contains a deity's creature ID (in position 1) and a
-- list of followers (position 2), generate those creatures within the rift.
function generate_deity_and_followers_in_rift(map_id, rift_y, rift_x, deity_and_followers)
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

  local cnt = 1

  -- Shuffle all the creatures' IDs so that there's a pleasing distribution
  -- in the rift.  
  cosmos_creatures = fn.shuffle(cosmos_creatures)

  -- Generate creatures in the rift area
  for ry = rift_y - 1, rift_y + 1 do
    for rx = rift_x - 1, rift_x + 1 do
      add_creature_to_map(cosmos_creatures[cnt], ry, rx, map_id, true)
      cnt = cnt + 1
    end
  end
end

-- Populate a deity and a selection of followers within the size-9 rift.
-- 
-- Shuffle the "non-Sceaudgenga" array, and iterate through it.  The first
-- deity in the shuffled array that has not been killed is generated along
-- with 8 followers in the rift region.
function populate_rift(map_id, rift_y, rift_x)
  local sceadu_details = {{"sceadugenga", {"teeming_mass_writhing_tentacles",
                                          "beast_beyond_furthest_star",
                                          "apocalyptic_hell_bears_no_name"}}}
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

  deity_details = fn.shuffle(deity_details)
  local generated = false

  for i = 1, #deity_details do
    local deity_and_followers = deity_details[i]
    local deity_creature_id = deity_and_followers[1]

    if get_num_creature_killed_global(deity_creature_id) == 0 then
      -- If the deity hasn't been killed yet, generate it and its followers
      -- within the rift
      generate_deity_and_followers_in_rift(map_id, rift_y, rift_x, deity_and_followers)
      generated = true
      
      add_message_with_pause("RIFT_REPOPULATE") 
      break
    end
  end

  if generated == false then
    cosmos_common.generate_deity_and_followers_in_rift(map_id, rift_y, rift_x, sceadu_details[1])
  end
end
