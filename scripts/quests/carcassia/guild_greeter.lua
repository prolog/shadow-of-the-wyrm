require('constants')

-- The friendly thief in the SW "house" in Carcassia A1.
message_sid = "CARCASSIA_THIEF_HOUSE_SID"

if creature_is_class(PLAYER_ID, CLASS_ID_THIEF) then
  message_sid = "CARCASSIA_THIEF_WELCOME_SID"
end

clear_and_add_message(message_sid)
