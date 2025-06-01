-- The friendly thief in the SW "house" in Carcassia A1.
messages = {"CARCASSIA_THIEF_HOUSE_SID", "CARCASSIA_THIEF_HOUSE2_SID"}
message_sid = messages[RNG_range(1, #messages)]

clear_and_add_message(message_sid)
