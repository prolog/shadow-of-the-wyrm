require('constants')
require('fn')
require('quest')

local pg_base_quest_id = "pitmistress_ghara_quest_"
local pg_quest_id = "pitmistress_ghara_quest_id"
local pg_quest_count = "pitmistress_ghara_quest_count"
local pg_banned = "pitmistress_ghara_banned"

local function ghara_quest_start_fn()
  local map_id = get_current_map_id()
  local y,x = 3,59
  local pl_y, pl_x = 8,63
  local player_level = get_creature_level(PLAYER_ID)
  local dl_min = math.min(player_level+2, 50)
  local dl_max = math.min(player_level+7, 50)

  local generated = generate_creature(map_id, CTILE_TYPE_DUNGEON_COMPLEX, y, x, dl_min, dl_max)

  if generated == true then
    -- Set the event script on the arena opponent.
    -- ...

    local cr_id = get_creature_id(y, x)
    teleport(PLAYER_ID, pl_y, pl_x)
  end

  return generated
end

local function ghara_quest_completion_condition_fn()
  return false
end

local function ghara_quest_completion_fn()
  -- ...

  return true
end

local function get_ghara_quest_count()
  local g_quest_count = 0

  local g_count_s = get_creature_additional_property(PLAYER_ID, pg_quest_count)
  if g_count_s ~= "" then
    g_quest_count = tonumber(g_count_s) + 1
  end

  return g_quest_count
end

local function get_quest_details()
  -- Generate the quest ID based on how many we've done before, or whether
  -- we're currently on one.
  local quest_id = get_creature_additional_property(PLAYER_ID, pg_quest_id)

  if quest_id == "" then
    -- Generate the quest ID based on the base plus the current quest
    -- counter.
    quest_id = pg_base_quest_id .. tostring(get_ghara_quest_count)
  end

  -- Generate the quest title and description
  local quest_title = "PITMISTRESS_GHARA_QUEST_TITLE_SID" .. "(" .. tostring(quest_count) .. ")"
  local quest_desc_sid = "PITMISTRESS_GHARA_QUEST_DESCRIPTION_SID"

  return quest_id, quest_title, quest_desc_sid
end

local function get_ghara_quest()
  local quest_id, quest_title_sid, quest_desc_sid = get_quest_details()

  local q = Quest:new(quest_id,
                      quest_title_sid,
                      "PITMISTRESS_GHARA_SHORT_DESCRIPTION_SID",
                      quest_desc_sid,
                      "PITMISTRESS_GHARA_QUEST_COMPLETE_SID",
                      "PITMISTRESS_GHARA_QUEST_REMINDER_SID",
                      truefn,
                      ghara_quest_start_fn,
                      ghara_quest_completion_condition_fn,
                      ghara_quest_completion_fn)

  return q
end

if get_creature_additional_property(PLAYER_ID, pg_banned) == "1" or get_creature_additional_property(PLAYER_ID, pg_quest_id) ~= "" then
  clear_and_add_message("PITMISTRESS_GHARA_BANNED_SID")
  set_creature_additional_property(PLAYER_ID, pg_banned, "1")
else
  if add_confirmation_message("PITMISTRESS_GHARA_FIGHT_QUERY_SID") then
    clear_and_add_message("PITMISTRESS_GHARA_FIGHT_ACCEPT_SID")

    local quest = get_ghara_quest()
    quest:execute()

    -- set_creature_additional_property(PLAYER_ID, pg_on_quest, "1")
  else
    clear_and_add_message("PITMISTRESS_GHARA_FIGHT_DECLINE_SID")
  end
end
