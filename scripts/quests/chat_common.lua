require('constants')
require('chat_common_races')

local cr_id = args[SPEAKING_CREATURE_ID]
local chat_script = args[CHAT_SCRIPT]

-- Do any speech based on the creature's race and current condition, then
-- run the usual chat script.
racial_speech(cr_id, get_race_id(cr_id))
run_chat_script(chat_script, cr_id)
