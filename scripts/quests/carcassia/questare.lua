require('constants')
require('quest')

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
  local nemesis_sids = {"QUESTARE_QUEST_NEMESIS_SID", "QUESTARE_QUEST_NEMESIS2_SID", "QUESTARE_QUEST_NEMESIS3_SID", "QUESTARE_QUEST_NEMESIS4_SID"}
  local nemesis_sid = nemesis_sids[RNG_range(1, #nemesis_sids)]

  add_message_with_pause("QUESTARE_QUEST_START_SID")
  clear_and_add_message(nemesis_sid, {creature_desc})
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
  remove_creature_additional_property(PLAYER_ID, q_qid)
  remove_creature_additional_property(PLAYER_ID, q_cur_quest)
  remove_creature_additional_property(PLAYER_ID, q_kill_count_before)
  remove_creature_additional_property(PLAYER_ID, q_creature_base_id)

  local y,x = get_creature_yx(PLAYER_ID)
  local min_danger = 1
  local level = get_creature_level(PLAYER_ID)
  local max_danger = level
  local extra_enchants = (level / 8) + RNG_range(1, 3)
  local num_items = RNG_range(1,2)
  local item_gen = false

  for i = 1, num_items do
    local gen, id = generate_item(y, x, min_danger, max_danger, extra_enchants)

    if gen then
      item_gen = true
    end
  end

  -- If for some reason an item couldn't be generated, then give the
  -- player some ivory.
  if item_gen == false then
    add_object_to_player_tile(CURRENCY_ID, level * 20)
  end
  
  clear_and_add_message("QUESTARE_QUEST_COMPLETE_SID")

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

local function get_quest(quest_id, quest_level, nemesis_id)
  local n_desc, n_short_desc = get_creature_description_sids(nemesis_id)
  local quest = Quest:new(quest_id,
                          {"QUESTARE_QUEST_TITLE_BASE_SID", tostring(quest_level)},
                          "QUESTARE_SHORT_DESCRIPTION_SID",
                          {"QUESTARE_QUEST_DESCRIPTION_SID", n_desc},
                          "QUESTARE_QUEST_COMPLETE_SID",
                          {"QUESTARE_QUEST_REMINDER_SID", n_desc},
                          truefn,
                          questare_quest_start_fn,
                          questare_quest_completion_condition_fn,
                          questare_quest_completion_fn)

  return quest
end

local function check_quest(quest)
  quest:execute()
end

local function init_quest(quest, quest_id, plvl, creature_base_id)
  if string.len(creature_base_id) == 0 then
    clear_and_add_message("QUESTARE_SPEECH_LATER_SID")
  else
    local creature_killed_before = get_num_creature_killed_global(creature_base_id)
    set_creature_additional_property(PLAYER_ID, q_kill_count_before, creature_killed_before)
    set_creature_additional_property(PLAYER_ID, q_creature_base_id, creature_base_id)
    set_creature_additional_property(PLAYER_ID, q_cur_quest, "1")
    set_creature_additional_property(PLAYER_ID, q_qid, quest_id)

    quest:execute()
  end
end

local function get_cached_questare_quest(questare_quest_id)
  local q_title_sid, qmaster_sid, map_name_sid, q_desc_sid, q_desc_params_sid = get_quest_details(questare_quest_id)
  local q = Quest:new(questare_quest_id,
                      q_title_sid,
                      qmaster_sid,
                      {q_desc_sid, q_desc_params_sid},
                      "QUESTARE_QUEST_COMPLETE_SID",
                      {"QUESTARE_QUEST_REMINDER_SID", q_desc_params_sid},
                      truefn,
                      questare_quest_start_fn,
                      questare_quest_completion_condition_fn,
                      questare_quest_completion_fn)
                      
  return q
end

if has_questare_quest() then
  local creature_quest_level = get_creature_additional_property(PLAYER_ID, q_quest_level)
  local creature_base_id = get_creature_additional_property(PLAYER_ID, q_creature_base_id)

  get_cached_questare_quest(questare_quest_id):execute()
else
  -- Can the player do a quest at the current level?
  local q_last_qid = get_creature_additional_property(PLAYER_ID, q_last_level)
  local creature_level = get_creature_level(PLAYER_ID)

  if q_last_qid ~= tostring(creature_level) then
    local quest_id = "questare_quest_" ..tostring(creature_level)
    local creature_base_id = get_random_hostile_creature_id(creature_level, creature_level, CTILE_TYPE_DUNGEON_COMPLEX)
    q = get_quest(quest_id, creature_level, creature_base_id)
    init_quest(q, quest_id, creature_level, creature_base_id)
  else
    clear_and_add_message("QUESTARE_SPEECH_LATER_SID")
  end
end

