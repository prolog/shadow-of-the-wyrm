require('constants')

local function increment_magic_skills()
  local skills = {{CSKILL_GENERAL_MAGIC, "SKILL_GENERAL_MAGIC_INCREMENT"},
                  {CSKILL_MAGIC_CANTRIPS, "SKILL_GENERAL_CANTRIPS_INCREMENT"}, 
                  {CSKILL_MAGIC_ARCANE, "SKILL_MAGIC_ARCANE_INCREMENT"}, 
                  {CSKILL_MAGIC_DIVINE, "SKILL_MAGIC_DIVINE_INCREMENT"}, 
                  {CSKILL_MAGIC_MYSTIC, "SKILL_MAGIC_MYSTIC_INCREMENT"}, 
                  {CSKILL_MAGIC_PRIMORDIAL, "CSKILL_MAGIC_PRIMORDIAL_INCREMENT"}}
  
  clear_and_add_message("ANCIENT_SAGE_SECRETS_SID")
  local incremented = false

  for i,v in ipairs(skills) do
    local skill_val = get_skill_value(PLAYER_ID, v[1])
    local incr_amt = 0
    
    if skill_val > 0 then
      if skill_val == 100 then
        max_skill_encountered = true
      else
        incr_amt = 10

        if skill_val > 90 then
          incr_amt = 100 - skill_val
        end

        incremented = true
        set_skill_value(PLAYER_ID, v[1], skill_val + incr_amt)
        add_message(v[2])
      end
    end
  end

  if incremented == false then
    if max_skill_encountered == true then
      add_spell_castings(PLAYER_ID, "c_15_shards", RNG_range(30, 50))
      clear_and_add_message("ANCIENT_SAGE_SHARDS_SID")
    else
      add_spell_castings(PLAYER_ID, "c_09_force_bolt", RNG_range(10, 15))
      clear_and_add_message("ANCIENT_SAGE_FORCE_BOLT_SID")
    end
  end
end

local function speak_to_sage(sage_id)
  local spoken_prop = "ANCIENT_SAGE_SPOKEN"
  local spoken = get_creature_additional_property(sage_id, spoken_prop)
  
  if spoken == "1" then
    clear_and_add_message("ANCIENT_SAGE_SPEECH_TEXT_SID")
  else
    local cantrips_val = get_skill_value(PLAYER_ID, CSKILL_MAGIC_CANTRIPS)
    local arcane_val = get_skill_value(PLAYER_ID, CSKILL_MAGIC_ARCANE)
    local divine_val = get_skill_value(PLAYER_ID, CSKILL_MAGIC_DIVINE)
    local mystic_val = get_skill_value(PLAYER_ID, CSKILL_MAGIC_MYSTIC)
    local primordial_val = get_skill_value(PLAYER_ID, CSKILL_MAGIC_PRIMORDIAL)

    if cantrips_val == 100 and arcane_val == 100 and divine_val == 100 and mystic_val == 100 and primordial_val == 100 then
      add_spell_castings(PLAYER_ID, "a_19_meteor", RNG_range(20, 30))
      clear_and_add_message("ANCIENT_SAGE_METEOR_SID")
    else
      increment_magic_skills()
    end

    set_creature_additional_property(sage_id, spoken_prop, "1")
  end
end

local sage_id = args[SPEAKING_CREATURE_ID]
speak_to_sage(sage_id)
