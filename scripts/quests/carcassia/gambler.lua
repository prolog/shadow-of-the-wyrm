local speech_sids = {"GAMBLER_SPEECH_TEXT_SID",
                     "GAMBLER_SPEECH_TEXT2_SID",
                     "GAMBLER_SPEECH_TEXT3_SID",
                     "GAMBLER_SPEECH_TEXT4_SID",
                     "GAMBLER_SPEECH_TEXT5_SID"}

clear_and_add_message(speech_sids[RNG_range(1, #speech_sids)])

