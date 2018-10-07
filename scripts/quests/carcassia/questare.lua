require('constants')

local q_qid = "questare_quest_id"
local q_last_level = "questare_last_quest_level"
local q_quest_level = "questare_quest_level"
local q_cur_quest = "questare_on_quest"
local q_kill_count_before = "questare_kill_count_before"
local q_creature_base_id = "questare_quest_creature_base_id"
local questare_quest_id = get_creature_additional_property(PLAYER_ID, q_qid)

local function questare_quest_start_fn()
  local creature_id = get_creature_additional_property(PLAYER_ID, q_creature_base_id)
  local creature_desc = get_creature_description(PLAYER_ID, creature_id, true)

  add_message_with_pause("QUESTARE_QUEST_START_SID")
  clear_and_add_message("QUESTARE_QUEST_START2_SID", {get_sid(creature_desc)})
end

local function questare_quest_completion_condition_fn()
  local kill_count_before = tonumber(get_creature_additional_property(PLAYER_ID, q_kill_count_before))
  local cur_kill_count = tonumber(get_num_creature_killed_global(get_creature_additional_property(PLAYER_ID, q_creature_base_id)))

  if cur_kill_count > kill_count_before then
    return true
  else
    return false
  end
end

local function questare_quest_completion_fn()
  -- ...

  return true
end

local function has_questare_quest()
  local on_quest = false
  local q_cur = get_creature_additional_property(PLAYER_ID, q_cur_quest)

  if q_cur == "1" then
    on_quest = true
  end

  return on_quest
end

local function get_quest(quest_level)
  local nemesis_id = get_creature_additional_property(PLAYER_ID, q_creature_base_id)
  local quest_title = get_sid("QUESTARE_QUEST_TITLE_BASE_SID") .. " (" .. tostring(quest_level) .. ")"
  local quest_desc = get_sid("QUESTARE_QUEST_DESCRIPTION_SID", {nemesis_id})
  local quest_reminder = get_sid("QUESTARE_QUEST_REMINDER_SID", {nemesis_id})

  local quest = Quest:new("questare_quest_" .. tostring(quest_level),
                          quest_title,
                          "QUESTARE_SHORT_DESCRIPTION_SID",
                          quest_desc,
                          "QUESTARE_QUEST_COMPLETE_SID",
                          quest_reminder,
                          truefn,
                          questare_quest_start_fn,
                          questare_quest_completion_condition_fn,
                          questare_quest_completion_fn)

  return quest
end

local function check_quest(quest)
  quest:execute()
end

local function init_quest(quest, plvl)
  local creature_base_id = get_random_hostile_creature_id(plvl, plvl)
  local creature_killed_before = get_num_creature_killed_global(creature_base_id)

  set_creature_additional_property(PLAYER_ID, q_kill_count_before, creature_killed_before)
  
  quest:execute()

  set_creature_additional_property(PLAYER_ID, q_creature_base_id, creature_base_id)
end

if has_questare_quest() then
  local creature_quest_level = get_creature_additional_property(PLAYER_ID, q_quest_level)
  check_quest(get_quest(creature_quest_level))
else
  if string.len(q_qid) > 0 then
  else
    -- Can the player do a quest at the current level?
    local q_last_qid = get_creature_additional_property(PLAYER_ID, q_last_level)
    local creature_level = get_creature_level(PLAYER_ID)

    if q_last_qid ~= tostring(creature_level) then
      q = get_quest(creature_level)
      init_quest(q, creature_level)
    else
      clear_and_add_message("QUESTARE_SPEECH_LATER_SID")
    end
  end
end

