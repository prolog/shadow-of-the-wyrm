require('constants')

-- It is particularly helpful to start out on Creator's Day!
function check_for_creation_day(cur_date)
  if cur_date == "09 01" then
    for i = 1, RNG_range(1, 5) do
      incr_str(PLAYER_ID, false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_dex(PLAYER_ID, false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_agi(PLAYER_ID, false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_int(PLAYER_ID, false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_wil(PLAYER_ID, false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_cha(PLAYER_ID, false)
    end

    add_message("SPECIAL_DAY_CREATORS_DAY")
  end
end

-- Some bonuses when playing on solstice/equinox.
-- Northern hemisphere dates are used.
function check_for_solstice_and_equinox(cur_date)
  if cur_date == "12 22" then
    for i = 1, RNG_range(4, 5) do
      incr_str(PLAYER_ID, false)
      incr_hea(PLAYER_ID, false)
    end
    
    add_message("SPECIAL_DAY_WINTER_SOLSTICE")
  elseif cur_date == "06 21" then
    for i = 1, RNG_range(4, 5) do
      incr_int(PLAYER_ID, false)
      incr_wil(PLAYER_ID, false)
    end

    add_message("SPECIAL_DAY_SUMMER_SOLSTICE")
  elseif cur_date == "03 20" then
    for i = 1, RNG_range(4, 5) do
      incr_cha(PLAYER_ID, false)
    end

    add_message("SPECIAL_DAY_SPRING_EQUINOX")
  elseif cur_date == "09 22" then
    for i = 1, RNG_range(2, 3) do
      incr_dex(PLAYER_ID, false)
      incr_agi(PLAYER_ID, false)
    end

    add_message("SPECIAL_DAY_FALL_EQUINOX")
  end
end

-- Check for certain dates using a "month day"-type format.
function check_for_special_day()
  local cur_date = os.date("%m %d")

  check_for_creation_day(cur_date)
  check_for_solstice_and_equinox(cur_date)
end

check_for_special_day()
