require('constants')
require('quest')

-- Joining the Guild of Thieves
local function join_guild_if_possible(pclass, guild_id)
  local can_join = false
  local desc_sid = "CARCASSIA_GUILD_THIEVES_MEMBERSHIP_SID"
  local excluded_guilds = HIGH_TOWER_GUILD_ID

  if pclass == CLASS_ID_THIEF then
    add_message_with_pause("GUILDMASTER_CARO_THIEF_SID")
    clear_messages()
    can_join = true
  elseif pclass == CLASS_ID_NOBLE then
    clear_and_add_message("GUILDMASTER_CARO_NOBLE_SID")
    return
  else
    -- People who aren't naturally thieves can prove their worth
    -- by breaking all their conducts.
    local num_conducts = get_num_conducts()
    local broken_conducts = get_creature_num_broken_conducts(PLAYER_ID)

    if broken_conducts == num_conducts then
      can_join = true
    end
  end

  if can_join then
    if add_confirmation_message("GUILDMASTER_CARO_JOIN_PROMPT_SID") then
     clear_and_add_message("GUILDMASTER_CARO_JOIN_ACCEPT_SID")
     add_membership(PLAYER_ID, guild_id, desc_sid, excluded_guilds)
    else
      clear_and_add_message("GUILDMASTER_CARO_JOIN_DECLINE_SID")
    end
  else
    add_message_with_pause("GUILDMASTER_CARO_INTRO_SID")
    clear_and_add_message("GUILDMASTER_CARO_INTRO2_SID")
  end
end

-- Quests
local function run_quests(hidden_room_quest, disarm_traps_quest)
  if hidden_room_quest:execute() == false then
    if disarm_traps_quest:execute() == false then
      add_message("GUILDMASTER_CARO_DEFAULT_SID")
    end
  end
end

-- Set up quests
local function hidden_room_start_fn()
  add_message_with_pause("GUILDMASTER_CARO_HIDDEN_ROOM_START_SID")
  clear_and_add_message("GUILDMASTER_CARO_HIDDEN_ROOM_START2_SID")
end

local function hidden_room_completion_condition_fn()
  -- If the feature isn't hidden, or isn't there, the player has
  -- sprung the teleport trap inside the hidden room.
  return tile_is_feature_hidden(4, 8, "carcassia_a1") == false
end

local function hidden_room_completion_fn()
  -- Guildmaster Caro teachers Disarm Traps.  If the player already
  -- has maxed skill in this, he teaches Thievery.  And if the player
  -- has mastered both, he has a very special present.

  local dtraps_value = get_skill_value(PLAYER_ID, CSKILL_GENERAL_DISARM_TRAPS)

  if dtraps_value < 100 then
    set_skill_value(PLAYER_ID, CSKILL_GENERAL_DISARM_TRAPS, dtraps_value + RNG_range(30, 40))
    add_message("GUILDMASTER_CARO_HIDDEN_ROOM_QUEST_COMPLETE_SID")
  else
    local thievery_value = get_skill_value(PLAYER_ID, CSKILL_GENERAL_THIEVERY)

    if thievery_value < 100 then
      set_skill_value(PLAYER_ID, CSKILL_GENERAL_THIEVERY, thievery_value + RNG_range(30, 40))
      add_message("GUILDMASTER_CARO_HIDDEN_ROOM_QUEST_COMPLETE_THIEVERY_SID")
    else
      add_object_to_player_tile("skeleton_key")
      add_message("GUILDMASTER_CARO_HIDDEN_ROOM_QUEST_COMPLETE_SKELETON_KEY_SID")
    end
  end

  return true
end

hidden_room_quest = Quest:new("hidden_room_quest",
                              "GUILDMASTER_CARO_HIDDEN_ROOM_QUEST_TITLE_SID",
                              "GUILDMASTER_CARO_SHORT_DESCRIPTION_SID",
                              "GUILDMASTER_CARO_HIDDEN_ROOM_DESCRIPTION_SID",
                              "GUILDMASTER_CARO_HIDDEN_ROOM_QUEST_COMPLETE_SID",
                              "GUILDMASTER_CARO_HIDDEN_ROOM_QUEST_REMINDER_SID",
                              truefn,
                              hidden_room_start_fn,
                              hidden_room_completion_condition_fn,
                              hidden_room_completion_fn)

local function disarm_traps_start_fn()
  add_message_with_pause("GUILDMASTER_CARO_DISARM_TRAPS_START_SID")
  add_message_with_pause("GUILDMASTER_CARO_DISARM_TRAPS_START2_SID")
  clear_and_add_message("GUILDMASTER_CARO_DISARM_TRAPS_START3_SID")
end

local function disarm_traps_completion_condition_fn()
  return (tile_has_feature(10, 55, "carcassia_b2") == false)
end

local function disarm_traps_completion_fn()
  add_message("GUILDMASTER_CARO_DISARM_TRAPS_QUEST_COMPLETE_SID")
  add_object_to_player_tile("_golden_apple", RNG_range(5, 10))
  return true
end

disarm_traps_quest = Quest:new("disarm_traps_quest",
                               "GUILDMASTER_CARO_DISARM_TRAPS_QUEST_TITLE_SID",
                               "GUILDMASTER_CARO_SHORT_DESCRIPTION_SID",
                               "GUILDMASTER_CARO_DISARM_TRAPS_DESCRIPTION_SID",
                               "GUILDMASTER_CARO_DISARM_TRAPS_QUEST_COMPLETE_SID",
                               "GUILDMASTER_CARO_DISARM_TRAPS_QUEST_REMINDER_SID",
                               truefn,
                               disarm_traps_start_fn,
                               disarm_traps_completion_condition_fn,
                               disarm_traps_completion_fn)

local guild_id = THIEVES_GUILD_ID
local player_class = get_class_id(PLAYER_ID)

if has_membership(PLAYER_ID, guild_id) then
  run_quests(hidden_room_quest, disarm_traps_quest)
elseif is_membership_excluded(PLAYER_ID, guild_id) then
  clear_and_add_message("GUILDMASTER_CARO_CANNOT_JOIN_SID")
else
  join_guild_if_possible(player_class, guild_id)
end
