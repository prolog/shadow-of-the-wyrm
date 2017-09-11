require('constants')
require('death')

local function generate_telari_staircase(creature_id, attacking_creature_id)
  -- Add the victory text.
  add_message_with_pause("GODSLAYER_WIN_MESSAGE")
  add_message_with_pause("GODSLAYER_WIN_MESSAGE2")
  add_message_with_pause("GODSLAYER_WIN_MESSAGE3")
  add_message_with_pause("GODSLAYER_WIN_MESSAGE4")
  add_message_with_pause("GODSLAYER_WIN_MESSAGE5")
  clear_messages()

  -- Sceadugenga is dead: the Nine have been destroyed.  Give the player
  -- the option to continue playing, or to exit.
  local keep_adventuring = add_confirmation_message("WIN_KEEP_ADVENTURING")
  
  -- Set the win condition for the godslayer ending.
  set_winner(PLAYER_ID, 3)

  if keep_adventuring == false then
    stop_playing_game(PLAYER_ID, true)
  else
    -- Create a staircase back to the top of the Cloudspire.
    local cur_map_id = get_current_map_id()
    local telari_top_map_id = "telari_top"
    local pl_y, pl_x = get_creature_yx(PLAYER_ID)

    map_transform_tile(cur_map_id, pl_y, pl_x, CTILE_TYPE_DOWN_STAIRCASE)
    map_add_tile_exit(cur_map_id, pl_y, pl_x, CDIRECTION_DOWN, telari_top_map_id)
    -- Remove the staircase at the top of the Cloudspire.  The shrine is now
    -- inert.
    map_transform_tile(telari_top_map_id, 9, 39, CTILE_TYPE_DAIS)
    map_remove_tile_exit(telari_top_map_id, 9, 39, CDIRECTION_UP)
  end
end

local way_back_fn = generate_telari_staircase
death.set_death_fn("sceadugenga", way_back_fn)

