require('quest')

-- Random information
local chat_topics = {"OLD_TOMER_SPEECH_TEXT_SID",
                     "OLD_TOMER_SPEECH_TEXT2_SID",
                     "OLD_TOMER_SPEECH_TEXT3_SID",
                     "OLD_TOMER_SPEECH_TEXT4_SID",
                     "OLD_TOMER_SPEECH_TEXT5_SID",
                     "OLD_TOMER_SPEECH_TEXT6_SID",
                     "OLD_TOMER_SPEECH_TEXT7_SID",
                     "OLD_TOMER_SPEECH_TEXT8_SID",
                     "OLD_TOMER_SPEECH_TEXT9_SID",
                     "OLD_TOMER_SPEECH_TEXT10_SID",
                     "OLD_TOMER_SPEECH_TEXT11_SID"}

clear_and_add_message(chat_topics[RNG_range(1, table.getn(chat_topics))])

