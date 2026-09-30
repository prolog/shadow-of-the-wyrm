require('constants')
require('chat_common_races')

local cr_id = args[SPEAKING_CREATURE_ID]
local chat_script = args[CHAT_SCRIPT]
local pct_chance = args[PCT_CHANCE]
local speech_text_sid = args[SPEECH_TEXT_SID]

-- Do any speech based on the creature's race and current condition, then
-- run the usual chat script.
racial_speech(cr_id, get_race_id(cr_id))

if string.len(chat_script) > 0 and RNG_percent_chance(pct_chance) then
  run_chat_script(chat_script, cr_id)
else
  if string.len(speech_text_sid) == 0 then
    speech_text_sid = "ACTION_CHAT_NO_RESPONSE"
  end

  clear_and_add_message(speech_text_sid)
end
