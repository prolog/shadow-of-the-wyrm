module(..., package.seeall)

require('constants')

function send_to_telari(creature_id)
  if creature_id == PLAYER_ID then
    play_music_event(CMUSIC_EVENT_PLANETARY_TELEPORT, false)
    add_message_with_pause("EAD_TELARI_CONFIRM_SID")
    load_map(creature_id, "telari")
  end
end

