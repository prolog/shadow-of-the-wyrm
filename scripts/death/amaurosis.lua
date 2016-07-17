require('death')

-- Win the game!
local function win(creature_id, attacking_creature_id)
  add_message_with_pause("WIN_MESSAGE", false)
  add_message_with_pause("WIN_MESSAGE2")
  add_message_with_pause("WIN_MESSAGE3")
  add_message_with_pause("WIN_MESSAGE4")
  local keep_adventuring = add_confirmation_message("WIN_KEEP_ADVENTURING")
    
  local player_id = "player"
  set_winner(player_id, 1) -- Regular win

  if keep_adventuring == false then
    stop_playing_game(player_id, true)
  end
end

local win_fn = win
death.set_death_fn("end_boss", win_fn)


