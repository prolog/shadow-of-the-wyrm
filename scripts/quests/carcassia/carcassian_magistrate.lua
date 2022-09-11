require('constants')
require('quest')

local function carcassian_magistrate_start_fn()
  add_message_with_pause("CARCASSIAN_MAGISTRATE_QUEST_START_SID")
  add_message_with_pause("CARCASSIAN_MAGISTRATE_QUEST_START2_SID")
  clear_and_add_message("CARCASSIAN_MAGISTRATE_QUEST_START3_SID")

  set_map_hostility("carcassia_guild_of_thieves", PLAYER_ID, false)
end

local function carcassian_magistrate_completion_condition_fn()
  return (get_num_creature_killed_global("guildmaster_caro") > 0)
end

local function carcassian_magistrate_completion_fn()
  clear_and_add_message("CARCASSIAN_MAGISTRATE_QUEST_COMPLETE_SID")

  add_object_to_player_tile(AMULET_OF_THE_SKY_ID)
  add_object_to_player_tile(SPEED_POTION_ID, RNG_range(4,6))
  add_object_to_player_tile(CURRENCY_ID, RNG_range(400, 500))

  return true
end

magistrate_quest = Quest:new("carcassian_magistrate_caro",
                             "CARCASSIAN_MAGISTRATE_QUEST_TITLE_SID",
                             "CARCASSIAN_MAGISTRATE_SHORT_DESCRIPTION_SID",
                             "CARCASSIAN_MAGISTRATE_QUEST_DESCRIPTION_SID",
                             "CARCASSIAN_MAGISTRATE_QUEST_COMPLETE_SID",
                             "CARCASSIAN_MAGISTRATE_QUEST_REMINDER_SID",
                             truefn,
                             carcassian_magistrate_start_fn,
                             carcassian_magistrate_completion_condition_fn,
                             carcassian_magistrate_completion_fn)

if magistrate_quest:execute() == false then
  clear_and_add_message("CARCASSIAN_MAGISTRATE_SPEECH_TEXT_SID")
end
