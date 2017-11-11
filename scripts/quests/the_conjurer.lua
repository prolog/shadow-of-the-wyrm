require('constants')

local function get_spellbooks()
  local spellbooks = {}

  spellbooks[tostring(CSKILL_MAGIC_CANTRIPS)] = "inferno_spellbook"
  spellbooks[tostring(CSKILL_MAGIC_ARCANE)] = "holocaust_spellbook"
  spellbooks[tostring(CSKILL_MAGIC_DIVINE)] = "divine_form_spellbook"
  spellbooks[tostring(CSKILL_MAGIC_MYSTIC)] = "malediction_spellbook"

  return spellbooks
end

local function get_highest_magic_skill(magic_skills)
  local highest_magic = -1
  local max_val = -1

  for k, v in pairs(magic_skills) do
    if v >= max_val then
      highest_magic, max_val = k, v
    end
  end

  return highest_magic, max_val
end

local function create_no_magic_reward()
  add_object_to_player_tile("inferno_wand")

  add_message_with_pause("THE_CONJURER_WAND_TEXT_SID")
  clear_and_add_message("THE_CONJURER_WAND_TEXT2_SID")
end

local function create_primordial_reward()
  add_spell_castings(PLAYER_ID, "p_09_antimatter", RNG_range(100, 150))
  add_spell_castings(PLAYER_ID, "p_10_annihilation", RNG_range(3, 5))
    
  add_message_with_pause("THE_CONJURER_PRIMORDIAL_TEXT_SID")
  add_message_with_pause("THE_CONJURER_PRIMORDIAL_TEXT2_SID")
  add_message_with_pause("THE_CONJURER_PRIMORDIAL_TEXT3_SID")
  add_message_with_pause("THE_CONJURER_PRIMORDIAL_TEXT4_SID")
  clear_and_add_message("THE_CONJURER_PRIMORDIAL_TEXT5_SID")
end

local function create_spellbook_reward(spellbooks, highest_magic)
  local spellbook_id = spellbooks[highest_magic]

  if spellbook_id ~= nil then
    add_object_to_player_tile(spellbook_id)

    add_message_with_pause("THE_CONJURER_SPELLBOOK_TEXT_SID")
    add_message_with_pause("THE_CONJURER_SPELLBOOK_TEXT2_SID")
    clear_and_add_message("THE_CONJURER_SPELLBOOK_TEXT3_SID")
  else
    log(CLOG_ERROR, "Null spellbook ID for The Conjurer!")
  end
end

if get_num_deities() == 0 then
  add_message_with_pause("THE_CONJURER_GODSLAYER_SPEECH_TEXT_SID")
  add_message_with_pause("THE_CONJURER_GODSLAYER_SPEECH_TEXT2_SID")
  clear_and_add_message("THE_CONJURER_GODSLAYER_SPEECH_TEXT3_SID")
else
  -- Determine which gift to give the player, and then set the gift
  -- property as generated.
  local conjurer_gift_key = "conjurer_gift_generated"
  local gift_generated = get_creature_additional_property(PLAYER_ID, conjurer_gift_key)

  if gift_generated ~= "1" then
    local spellbooks = get_spellbooks()

    local magic_skills = get_magic_skills(PLAYER_ID)
    table.sort(magic_skills)

    -- Halve the value of Cantrips.  If it's very high and the other skills
    -- are very low, it should still be considered for the Conjurer's reward.
    -- But for example, if the player has maxed Cantrips and Primordial,
    -- the player should always get the witchling reward.
    if magic_skills[CSKILL_MAGIC_CANTRIPS] ~= nil then
      magic_skills[CSKILL_MAGIC_CANTRIPS] = (magic_skills[C_SKILL_MAGIC_CANTRIPS] / 2)
    end

    local highest_magic, max_val = get_highest_magic_skill(magic_skills)

    -- If the player has no magic skills, he or she gets a wand of inferno.
    if max_val == 0 or highest_magic == -1 then
      create_no_magic_reward()
    -- Primordial casters get access to antimatter.
    elseif highest_magic == tostring(CSKILL_MAGIC_PRIMORDIAL) then
      create_primordial_reward()
    -- Cantrips users get a spellbook of Inferno.
    elseif highest_magic == tostring(CSKILL_MAGIC_CANTRIPS) then
      local spellbook_id = spellbooks[highest_magic]
      add_object_to_player_tile(spellbook_id)

      add_message_with_pause("THE_CONJURER_CANTRIPS_TEXT_SID")
      clear_and_add_message("THE_CONJURER_CANTRIPS_TEXT2_SID")
    -- Spellcasters get a copy of a mega-spellbook.
    else
      create_spellbook_reward(spellbooks, highest_magic)
    end

    set_creature_additional_property(PLAYER_ID, conjurer_gift_key, "1")
  else
    clear_and_add_message("THE_CONJURER_SPEECH_TEXT_SID")
  end
end
