-- It is particularly helpful to start out on Creator's Day!
function check_for_creation_day(cur_date)
  if cur_date == "09 01" then
    for i = 1, RNG_range(1, 5) do
      incr_str("player", false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_dex("player", false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_agi("player", false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_int("player", false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_wil("player", false)
    end

    for i = 1, RNG_range(1, 5) do
      incr_cha("player", false)
    end

    add_message("SPECIAL_DAY_CREATORS_DAY")
  end
end

-- Check for certain dates using a "month day"-type format.
function check_for_special_day()
  local cur_date = os.date("%m %d")

  check_for_creation_day(cur_date)
end

check_for_special_day()
