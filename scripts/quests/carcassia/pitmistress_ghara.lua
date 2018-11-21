require('constants')
require('fn')
require('quest')

local pg_base_quest_id = "pitmistress_ghara_quest_"
local pg_quest_id = "pitmistress_ghara_quest_id"
local pg_quest_count = "pitmistress_ghara_quest_count"
local pg_banned = "pitmistress_ghara_banned"
local pg_gift_generated = "pitmistress_ghara_gift_generated"
local pg_cur_q_complete = "pitmistress_ghara_current_quest_complete"
local pg_on_quest = "pitmistress_ghara_on_quest"
local max_ghara_quests = 10

local function get_ghara_quest_count()
  local g_quest_count = 1

  local g_count_s = get_creature_additional_property(PLAYER_ID, pg_quest_count)
  if g_count_s ~= "" then
    g_quest_count = tonumber(g_count_s) + 1
  end

  return g_quest_count
end

local function ghara_quest_start_fn()
  local map_id = get_current_map_id()
  local y,x = 3,59
  local pl_y, pl_x = 8,63
  local player_level = get_creature_level(PLAYER_ID)
  local dl_min = math.min(player_level+2, 50)
  local dl_max = math.min(player_level+7, 50)

  local generated = generate_creature(map_id, CTILE_TYPE_DUNGEON_COMPLEX, y, x, dl_min, dl_max)

  if generated == true then
    -- Set the event script on the fighting pits opponent.
    local cr_id = get_creature_id(y, x, map_id)
    set_event_script(cr_id, map_id, "death/fighting_pits.lua", CCREATURE_EVENT_SCRIPT_DEATH, 100)
    set_creature_additional_property(PLAYER_ID, pg_on_quest, "1")

    local cr_id = get_creature_id(y, x)
    teleport(PLAYER_ID, pl_y, pl_x)
  end

  return generated
end

local function ghara_quest_completion_condition_fn()
  return get_creature_additional_property(PLAYER_ID, pg_cur_q_complete) == "1"
end

local function ghara_quest_completion_fn()
  remove_creature_additional_property(PLAYER_ID, pg_cur_q_complete)
  remove_creature_additional_property(PLAYER_ID, pg_on_quest)
  
  local new_quest_count = get_ghara_quest_count() + 1
  set_creature_additional_property(PLAYER_ID, pg_quest_count, tostring(new_quest_count))

  if new_quest_count > max_ghara_quests then
    add_message_with_pause("PITMISTRESS_GHARA_DONE_SID")
    clear_and_add_message("PITMISTRESS_GHARA_BOW_SID")

    add_object_to_player_tile("qaali")
  else
    local item_ids = {SILVERWEED_ID, GAIN_ATTRIBUTES_POTION_ID, GOLDEN_APPLE_ID, SILVER_APPLE_ID}

    clear_and_add_message("PITMISTRESS_GHARA_QUEST_COMPLETE_SID")

    add_object_to_player_tile(item_ids[RNG_range(1, #item_ids)], RNG_range(1,2))
    add_object_to_player_tile(CURRENCY_ID, RNG_range(20, 50))
  end


  return true
end

local function get_quest_details()
  -- Generate the quest ID based on how many we've done before, or whether
  -- we're currently on one.
  local quest_id = get_creature_additional_property(PLAYER_ID, pg_quest_id)
  local quest_count_s = tostring(get_ghara_quest_count())

  if quest_id == "" then
    -- Generate the quest ID based on the base plus the current quest
    -- counter.
    quest_id = pg_base_quest_id .. quest_count_s
  end

  -- Generate the quest title and description
  local quest_title = {"PITMISTRESS_GHARA_QUEST_TITLE_SID", quest_count_s}
  local quest_desc_sid = "PITMISTRESS_GHARA_QUEST_DESCRIPTION_SID"

  return quest_id, quest_title, quest_desc_sid
end

local function get_ghara_quest()
  local quest_id, quest_title, quest_desc_sid = get_quest_details()

  local q = Quest:new(quest_id,
                      quest_title,
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

local function done_ghara_quests()
  return is_quest_completed(pg_base_quest_id .. tostring(max_ghara_quests))
end

local function ban_player()
  clear_and_add_message("PITMISTRESS_GHARA_BANNED_SID")
  set_creature_additional_property(PLAYER_ID, pg_banned, "1")
end

local quest = get_ghara_quest()

if done_ghara_quests() then
  clear_and_add_message("PITMISTRESS_GHARA_BOW_SID")
else
  -- If the player's already on a Ghara quest, see if they're done.
  if get_creature_additional_property(PLAYER_ID, pg_on_quest) == "1" then
    quest:execute()    
  else  
    -- Not currently on a Ghara quest.  Confirm before teleporting into
    -- the fighting pits.
    if add_confirmation_message("PITMISTRESS_GHARA_FIGHT_QUERY_SID") then
      clear_and_add_message("PITMISTRESS_GHARA_FIGHT_ACCEPT_SID")
      quest:execute()
    else
      clear_and_add_message("PITMISTRESS_GHARA_FIGHT_DECLINE_SID")
    end
  end
end
