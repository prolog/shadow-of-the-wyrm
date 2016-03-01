require('death')

-- Win the game!
local function win(creature_id, attacking_creature_id)
  -- To do: eventually prompt the player for whether they want to
  -- continue or not, track the win in-game for later, etc.
  add_message_with_pause("WIN_MESSAGE")
  
  local player_id = "player"
  set_winner(player_id)
  stop_playing_game(player_id, true)
end

local win_fn = win
death.set_death_fn("end_boss", win_fn)


