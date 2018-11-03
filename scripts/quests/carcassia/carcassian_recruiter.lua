require('constants')
require('quest')

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

if garros_quest:execute() == false then
  if camp_quest:execute() == false then
    clear_and_add_message("CARCASSIAN_RECRUITER_SPEECH_TEXT_SID")
  end
end
