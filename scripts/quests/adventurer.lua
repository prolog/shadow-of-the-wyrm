require('constants')

local function request_follow(this_cr_id, name)
  if add_confirmation_message("ADVENTURER_FOLLOW_SID", {name}) then
    incr_str_to_unburdened(this_cr_id, false)

    set_leader(this_cr_id, PLAYER_ID)
    set_adventurers_joined(PLAYER_ID, get_adventurers_joined(PLAYER_ID) + 1)
    order_follow(this_cr_id, PLAYER_ID)

    -- Set the chat text
    set_creature_speech_text_sid(this_cr_id, "ADVENTURER_SPEECH_TEXT" .. tostring(RNG_range(1, 7)) .. "_SID")

    -- Let's go!
    clear_and_add_message("ADVENTURER_SPEECH_LETS_GO_SID")
  else
    clear_and_add_message("ADVENTURER_FOLLOW_DECLINE_SID", {name})
  end
end

local this_cr_id = args[SPEAKING_CREATURE_ID]
local leader_id = get_leader_id(this_cr_id)
local name = get_name(this_cr_id)

if leader_id == PLAYER_ID then
  add_message(get_creature_speech_text_sid(this_cr_id), {name})
else
  request_follow(this_cr_id, name)
end

