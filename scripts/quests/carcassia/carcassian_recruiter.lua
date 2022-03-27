require('constants')
require('quest')

local cr_id = args[SPEAKING_CREATURE_ID]
local rebel_map_id = "carcassia_a1"

-- There's a minor rebellion - go quell it.
local function carcassian_recruiter_rebels_start_fn()
  add_message_with_pause("CARCASSIAN_RECRUITER_REBELS_QUEST_START_SID")
  add_message_with_pause("CARCASSIAN_RECRUITER_REBELS_QUEST_START2_SID")
  clear_and_add_message("CARCASSIAN_RECRUITER_REBELS_QUEST_START3_SID")

  local num_rebels = RNG_range(12, 16)
  local rebel_ids = {ARCHER_ID, FARMER_ID, FISHERMAN_ID, THATCHER_ID, TRADESMAN_ID}
  local weapon_ids = {SPEAR_ID, LONG_SPEAR_ID, MACE_ID}

  for i = 1, num_rebels do
    local y = RNG_range(10,19)
    local x = RNG_range(52,79)
    
    local c_id = add_creature_to_map(rebel_ids[RNG_range(1, #rebel_ids)], y, x, rebel_map_id, true)

    if string.len(c_id) > 0 then
      set_creature_additional_property(c_id, QUEST_CARCASSIAN_RECRUITER_REBEL_CREATURE, "1", rebel_map_id)
    
      -- ensure we can't get quests from the rebels...
      remove_chat_script(c_id, rebel_map_id)

      add_object_to_creature(rebel_map_id, c_id, weapon_ids[RNG_range(1, #weapon_ids)])
    end
  end

  set_creature_additional_property(cr_id, QUEST_CARCASSIAN_RECRUITER_REBEL_CREATURE, "1")
end

local function carcassian_recruiter_rebels_completion_condition_fn()
  local cr_gen = get_creature_additional_property(cr_id, QUEST_CARCASSIAN_RECRUITER_REBEL_CREATURE)
  
  return (cr_gen == "1" and count_creatures_with_property(QUEST_CARCASSIAN_RECRUITER_REBEL_CREATURE, "1", rebel_map_id) == 0)
end

local function carcassian_recruiter_rebels_completion_fn()
  local level = get_creature_level(PLAYER_ID)
  local amount = 1000 - (200 * level)

  if amount < 100 then
    amount = 100
  end
  
  clear_and_add_message("CARCASSIAN_RECRUITER_REBELS_QUEST_COMPLETE_SID")
  add_object_to_player_tile(CURRENCY_ID, amount)
  remove_creature_additional_property(cr_id, QUEST_CARCASSIAN_RECRUITER_REBEL_CREATURE)

  return true
end

rebels_quest = Quest:new("recruiter_rebels",
                         "CARCASSIAN_RECRUITER_REBELS_QUEST_TITLE_SID",
                         "CARCASSIAN_RECRUITER_SHORT_DESCRIPTION_SID",
                         "CARCASSIAN_RECRUITER_REBELS_QUEST_DESCRIPTION_SID",
                         "CARCASSIAN_RECRUITER_REBELS_QUEST_COMPLETE_SID",
                         "CARCASSIAN_RECRUITER_REBELS_QUEST_REMINDER_SID",
                         truefn,
                         carcassian_recruiter_rebels_start_fn,
                         carcassian_recruiter_rebels_completion_condition_fn,
                         carcassian_recruiter_rebels_completion_fn)

-- Track down and kill Garros
local function carcassian_recruiter_garros_start_fn()
  add_message_with_pause("CARCASSIAN_RECRUITER_GARROS_QUEST_START_SID")
  add_message_with_pause("CARCASSIAN_RECRUITER_GARROS_QUEST_START2_SID")
  clear_and_add_message("CARCASSIAN_RECRUITER_GARROS_QUEST_START3_SID")
end

local function carcassian_recruiter_garros_completion_condition_fn()
  return (get_num_creature_killed_global("garros") > 0)
end

local function carcassian_recruiter_garros_completion_fn()
  add_message_with_pause("CARCASSIAN_RECRUITER_GARROS_QUEST_COMPLETE_SID")
  clear_and_add_message("CARCASSIAN_RECRUITER_GARROS_QUEST_COMPLETE2_SID")

  add_membership(PLAYER_ID, "carcassian_irregulars", "CARCASSIAN_IRREGULARS_MEMBERSHIP_SID")
  add_object_to_player_tile("barbed_spear", RNG_range(5,7))
  add_object_to_player_tile("tower_shield")
  add_object_to_player_tile(CURRENCY_ID, RNG_range(20, 30))

  return true
end

garros_quest = Quest:new("recruiter_garros",
                         "CARCASSIAN_RECRUITER_GARROS_QUEST_TITLE_SID",
                         "CARCASSIAN_RECRUITER_SHORT_DESCRIPTION_SID",
                         "CARCASSIAN_RECRUITER_GARROS_QUEST_DESCRIPTION_SID",
                         "CARCASSIAN_RECRUITER_GARROS_QUEST_COMPLETE_SID",
                         "CARCASSIAN_RECRUITER_GARROS_QUEST_REMINDER_SID",
                         truefn,
                         carcassian_recruiter_garros_start_fn,
                         carcassian_recruiter_garros_completion_condition_fn,
                         carcassian_recruiter_garros_completion_fn)
		       
-- Clear out the Ogre camp
local function carcassian_recruiter_camp_start_fn()
  add_message_with_pause("CARCASSIAN_RECRUITER_CAMP_QUEST_START_SID")
  add_message_with_pause("CARCASSIAN_RECRUITER_CAMP_QUEST_START2_SID")
  clear_and_add_message("CARCASSIAN_RECRUITER_CAMP_QUEST_START3_SID")
end

local function carcassian_recruiter_camp_completion_condition_fn()
  return (get_num_creature_killed_global("urgrim") > 0)
end

local function carcassian_recruiter_camp_completion_fn()
  add_message_with_pause("CARCASSIAN_RECRUITER_CAMP_QUEST_COMPLETE_SID")
  clear_and_add_message("CARCASSIAN_RECRUITER_CAMP_QUEST_COMPLETE2_SID")

  add_object_to_player_tile(GOLDEN_APPLE_ID, RNG_range(2,4))
  add_object_to_player_tile("dragon_helm")
  add_object_to_player_tile(CURRENCY_ID, RNG_range(30, 50))

  return true
end

camp_quest = Quest:new("recruiter_ogre_camp",
                       "CARCASSIAN_RECRUITER_CAMP_QUEST_TITLE_SID",
                       "CARCASSIAN_RECRUITER_SHORT_DESCRIPTION_SID",
                       "CARCASSIAN_RECRUITER_CAMP_QUEST_DESCRIPTION_SID",
                       "CARCASSIAN_RECRUITER_CAMP_QUEST_COMPLETE_SID",
                       "CARCASSIAN_RECRUITER_CAMP_QUEST_REMINDER_SID",
                       truefn,
                       carcassian_recruiter_camp_start_fn,
                       carcassian_recruiter_camp_completion_condition_fn,
                       carcassian_recruiter_camp_completion_fn)

if rebels_quest:execute() == false then
  if garros_quest:execute() == false then
    if camp_quest:execute() == false then
      clear_and_add_message("CARCASSIAN_RECRUITER_SPEECH_TEXT_SID")
    end
  end
end