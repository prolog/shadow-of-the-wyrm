require('constants')
require('tame')

-- Win the game!
local function tame_win(creature_id, attacking_creature_id, map_id)
  add_message_with_pause("TAME_WIN_MESSAGE")
  add_message_with_pause("TAME_WIN_MESSAGE2")
  add_message_with_pause("TAME_WIN_MESSAGE3")
  add_message_with_pause("TAME_WIN_MESSAGE4")

  local keep_adventuring = add_confirmation_message("WIN_KEEP_ADVENTURING", true)
    
  set_winner(PLAYER_ID, CCREATURE_WIN_REGULAR)

  if keep_adventuring == false then
    stop_playing_game(PLAYER_ID, true)
  end
end

local tame_win_fn = tame_win
tame.set_tame_fn("end_boss", tame_win_fn)

