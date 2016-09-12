require('constants')
require('death')

-- Win the game!
local function win(creature_id, attacking_creature_id)
  add_message_with_pause("WIN_MESSAGE", false)
  add_message_with_pause("WIN_MESSAGE2")
  add_message_with_pause("WIN_MESSAGE3")
  add_message_with_pause("WIN_MESSAGE4")
  local keep_adventuring = add_confirmation_message("WIN_KEEP_ADVENTURING")
    
  set_winner(PLAYER_ID, 1) -- Regular win

  if keep_adventuring == false then
    stop_playing_game(PLAYER_ID, true)
  end
end

local win_fn = win
death.set_death_fn("end_boss", win_fn)


