require('constants')

local cr_id = args[SPEAKING_CREATURE_ID]
local chat_script = args[CHAT_SCRIPT]

run_chat_script(chat_script, cr_id)
