local oracle_sids = {"BLIND_ORACLE_SPEECH_TEXT_SID",
                     "BLIND_ORACLE_SPEECH_TEXT2_SID",
                     "BLIND_ORACLE_SPEECH_TEXT3_SID",
                     "BLIND_ORACLE_SPEECH_TEXT4_SID",
                     "BLIND_ORACLE_SPEECH_TEXT5_SID",
                     "BLIND_ORACLE_SPEECH_TEXT6_SID",
                     "BLIND_ORACLE_SPEECH_TEXT7_SID",
                     "BLIND_ORACLE_SPEECH_TEXT8_SID",
                     "BLIND_ORACLE_SPEECH_TEXT9_SID",
                     "BLIND_ORACLE_SPEECH_TEXT10_SID",
                     "BLIND_ORACLE_SPEECH_TEXT11_SID",
                     "BLIND_ORACLE_SPEECH_TEXT12_SID",
                     "BLIND_ORACLE_SPEECH_TEXT13_SID",
                     "BLIND_ORACLE_SPEECH_TEXT14_SID",
                     "BLIND_ORACLE_SPEECH_TEXT15_SID",
                     "BLIND_ORACLE_SPEECH_TEXT16_SID",
                     "BLIND_ORACLE_SPEECH_TEXT17_SID",
                     "BLIND_ORACLE_SPEECH_TEXT18_SID",
                     "BLIND_ORACLE_SPEECH_TEXT19_SID",
                     "BLIND_ORACLE_SPEECH_TEXT20_SID"}

local sid = oracle_sids[RNG_range(1, #oracle_sids)]

clear_and_add_message(sid)
