require('death')

-- Win the game!
local function win(creature_id, attacking_creature_id)
    stop_playing_game("player", true)

    -- To do: eventually prompt the player for whether they want to
    -- continue or not, track the win in-game for later, etc.
    add_message_with_pause("WIN_MESSAGE")
end

local win_fn = win
death.set_death_fn("end_boss", win_fn)


