require('constants')

local cr_id = args[SPEAKING_CREATURE_ID]

-- Famous last words, but there's no way I should ever need more than 100
-- pieces of music for a given NPC.
local MAX_SONGS = 100

local function get_songs()
  local songs = {}

  local prefix = "CREATURE_PROPERTIES_SONG"
  local prop = ""
  local i = 1
  local found = true

  while found == true do
    song = {get_creature_additional_property_csv(cr_id, prefix .. tostring(i))}

    if #song < 2 then
      found = false
    else
      songs[i] = {song[1], song[2]}
      i = i + 1
    end

    if i > MAX_SONGS then
      break
    end
  end

  return songs
end

local function select_music(songs)
  local loc = ""
  local song_menu = {}

  for i,v in ipairs(songs) do
    local name_sid = v[1]
    local location = v[2]

    table.insert(song_menu, location .. "=" .. get_sid(name_sid))
  end

  loc = create_menu("MUSICIAN_REQUEST_MUSIC", song_menu)
  return loc
end

if is_music_enabled() then
  songs = get_songs()

  if #songs == 0 then
    clear_and_add_message("MUSICIAN_NO_SONGS")
  else  
    local song_location = select_music(songs)

    if #song_location > 0 then
      play_music_location(song_location, false)
      add_message_with_pause("MUSICIAN_PERFORMANCE")
      play_map_music()
      clear_and_add_message("MUSICIAN_PERFORMANCE_OVER")
    else
      -- If nothing else is selected, play something generic.
      clear_and_add_message("MUSICIAN_NO_MUSIC_SELECTED")
    end
  end
else
  clear_and_add_message("MUSICIAN_MUSIC_DISABLED")
end
