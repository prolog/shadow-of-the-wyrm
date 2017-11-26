require('constants')
require('fn')

local melee_skills = {CSKILL_MELEE_AXES, CSKILL_MELEE_SHORT_BLADES,
                      CSKILL_MELEE_LONG_BLADES, CSKILL_MELEE_BLUDGEONS,
                      CSKILL_MELEE_DAGGERS, CSKILL_MELEE_RODS_AND_STAVES,
                      CSKILL_MELEE_SPEARS, CSKILL_MELEE_UNARMED,
                      CSKILL_MELEE_WHIPS, CSKILL_MELEE_EXOTICS}

local ranged_skills = {CSKILL_RANGED_AXES, CSKILL_RANGED_BLADES,
                       CSKILL_RANGED_BLUDGEONS, CSKILL_RANGED_BOWS,
                       CSKILL_RANGED_CROSSBOWS, CSKILL_RANGED_DAGGERS,
                       CSKILL_RANGED_ROCKS, CSKILL_RANGED_SLINGS,
                       CSKILL_RANGED_SPEARS, CSKILL_RANGED_EXOTIC}

-- Return a table of skills for the creature ID whose values are the
-- maximum of 100.  This table may be empty.
local function get_max_valued_skills(cr_id, skills)
  local maxed_skills = {}

  for i,v in pairs(skills) do
    local skill_val = get_skill_value(cr_id, v)

    if skill_val == 100 then
      maxed_skills[v] = skill_val
    end
  end

  return maxed_skills
end

-- Check to see if the creature prefers ranged combat to melee.  This is
-- the case if the creature is an archer, or if the creature has more
-- maxed ranged weapon skills than melee.
local function prefers_ranged_combat(cr_id, class_id)
  local mskills = get_max_valued_skills(cr_id, melee_skills)
  local rskills = get_max_valued_skills(cr_id, ranged_skills)

  local m_sz = fn.atable_size(mskills)
  local r_sz = fn.atable_size(rskills)

  if (r_sz > m_sz) or class_id == "archer" then
    return true
  else
    return false
  end
end

local function give_ranged_gift(cr_id)
  local ranged_gifts = {[CSKILL_RANGED_AXES] = {"elysian_throwing_axe", 6},
                        [CSKILL_RANGED_BLADES] = {"elysian_throwing_sword", 6},
                        [CSKILL_RANGED_BLUDGEONS] = {"titanic_heavenly_pillar", 1},
                        [CSKILL_RANGED_BOWS] = {"arrow_ancient_magics", 50},
                        [CSKILL_RANGED_CROSSBOWS] = {"bolt_ancient_magics", 50},
                        [CSKILL_RANGED_DAGGERS] = {"tooth_ancient_sea_creature", 15},
                        [CSKILL_RANGED_ROCKS] = {"massive_ferric_meteorite", 1},
                        [CSKILL_RANGED_SLINGS] = {"antimatter_shot", 75},
                        [CSKILL_RANGED_SPEARS] = {"spine_ancient_horror", 6},
                        [CSKILL_RANGED_EXOTIC] = {"chaos_bomb", "24"}}

  local ranged_skills = get_max_valued_skills(cr_id, ranged_skills)
  local sz = fn.atable_size(ranged_skills)
  local gift_skill = CSKILL_RANGED_BOWS

  for k,v in pairs(ranged_skills) do
    gift_skill = k
  end

  -- Get the gift details for this skill.  Add the item and an
  -- appropriate stack size to the player's tile.
  local gift_details = ranged_gifts[gift_skill]
  
  if gift_details ~= nil then
    add_message_with_pause("THE_SMITH_RANGED_GIFT_SID")
    add_message_with_pause("THE_SMITH_RANGED_GIFT2_SID")
    clear_and_add_message("THE_SMITH_RANGED_GIFT3_SID")

    add_object_to_player_tile(gift_details[1], gift_details[2])
  end
end

if get_num_deities() == 0 then
  clear_and_add_message("THE_SMITH_GODSLAYER_SPEECH_TEXT_SID")
else
  local divine_race_id = "_divine"
  local smith_prop = "the_smith_gift_generated"
  local given_gift = get_creature_additional_property(PLAYER_ID, smith_prop)

  if string.len(given_gift) == 0 then
    local class_id = get_class_id(PLAYER_ID)
    
    if prefers_ranged_combat(PLAYER_ID, class_id) then
      give_ranged_gift(PLAYER_ID)
    else
      local num_dice, num_sides, modifier = get_creature_base_damage(PLAYER_ID)
      local level = get_creature_level(PLAYER_ID)

      if class_id == "pugilist" then
        add_message_with_pause("THE_SMITH_SPEECH_UNARMED_SID")

        -- If the player is skilled at unarmed combat, then:
        --
        -- 1. Give a large damage increase
        
        modifier = modifier + 400
        
        --
        -- 2. If the player doesn't have slay divine, grant it.  If the player
        --    has that slay, grant an additional stack of damage.
        local slays = {get_unarmed_slays(PLAYER_ID)}

        if fn.contains(slays, divine_race_id) then
          modifier = modifier + 250
          clear_and_add_message("THE_SMITH_SPEECH_UNARMED_SLAY_SID")
        else
          add_unarmed_slay(PLAYER_ID, divine_race_id)
          clear_and_add_message("THE_SMITH_SPEECH_UNARMED_NO_SLAY_SID")
        end

        set_creature_base_damage(PLAYER_ID, num_dice, num_sides, modifier)
      else
        -- If the creature has Dual Wield skill, there's a <skill>% chance of
        -- being given the Shard of Starlight.
        local dual_wield = get_skill_value(PLAYER_ID, CSKILL_GENERAL_DUAL_WIELD)
        if RNG_percent_chance(dual_wield) then
          add_message_with_pause("THE_SMITH_SPEECH_SHARD_SID")
          add_message_with_pause("THE_SMITH_SPEECH_SHARD2_SID")
          add_message_with_pause("THE_SMITH_SPEECH_SHARD3_SID")
          clear_and_add_message("THE_SMITH_SPEECH_SHARD4_SID")

          add_object_to_player_tile("shard_starlight")
        else
          -- If the creature doesn't meet the unarmed/dual wield requirements,
          -- grant the God-Blade.
          add_message_with_pause("THE_SMITH_SPEECH_GODBLADE_SID")
          add_message_with_pause("THE_SMITH_SPEECH_GODBLADE2_SID")
          add_message_with_pause("THE_SMITH_SPEECH_GODBLADE3_SID")
          add_message_with_pause("THE_SMITH_SPEECH_GODBLADE4_SID")
          clear_and_add_message("THE_SMITH_SPEECH_GODBLADE5_SID")

          add_object_to_player_tile("godblade")
        end
      end
    end
    
    -- Set the gift property so that this'll be skipped next time.
    set_creature_additional_property(PLAYER_ID, smith_prop, "1")
  else
    clear_and_add_message("THE_SMITH_SPEECH_TEXT_SID")
  end
end
