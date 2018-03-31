require('constants')

local function join_guild_if_possible(pclass, guild_id)
  local can_join = false
  local desc_sid = "CARCASSIA_GUILD_THIEVES_MEMBERSHIP_SID"
  local excluded_guilds = "tower_of_wizardry"

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

-- JCD TODO: Checks once the creature has actually joined the guild
-- (for quests, etc).
local guild_id = "carassia_guild_thieves"
local player_class = get_class_id(PLAYER_ID)

if has_membership(PLAYER_ID, guild_id) then
  -- ...
elseif is_membership_excluded(PLAYER_ID, guild_id) then
  clear_and_add_message("GUILDMASTER_CARO_CANNOT_JOIN_SID")
else
  join_guild_if_possible(player_class, guild_id)
end
