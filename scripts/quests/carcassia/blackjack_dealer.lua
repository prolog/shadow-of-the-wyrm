require('dealer')

local hit_id = "hit"
local stay_id = "stay"

-- Return a string representation of the card
local function get_card_value(card)
  local card_values = {"A", "2", "3", "4",
                       "5", "6", "7", "8",
                       "9", "10", "J", "Q", "K"}

  return card_values[card]
end

-- Draw a card out of the deck and into the given hand.
local function draw_card(deck, hand)
  if #deck > 0 then
    local idx = RNG_range(1, #deck)
    local card = table.remove(deck, idx)
    table.insert(hand, card)
  end
end

-- Returns a string summarizing the given hand.
local function get_hand_msg(base_sid, cards, score)
  msg = get_sid(base_sid)

  for k,v in ipairs(cards) do
    msg = msg .. get_card_value(v)

    if k ~= #cards then
      msg = msg .. ", "
    end
  end

  msg = msg .. " (" .. tostring(score) .. "). "

  return msg
end

-- Returns a deck of cards, as an array
-- 1 = A
-- 2-10 = card values
-- 11, 12, 13 = Jack, Queen, King
local function create_deck()
  local cards = {}

  for i = 1,13 do
    for j = 1, 4 do
      table.insert(cards, i)
    end
  end

  return cards
end

-- The score for a blackjack hand is:
-- Face value: 2-10
-- 10: J, Q, K
-- 1/10: A.  Ace counts as 10, except when that would put the hand
-- over 21, at which point it counts as 1.
local function calculate_score(orig_hand)
  local score = 0
  local num_aces = 0
  local hand = {}

  for i = 1, #orig_hand do
    local card = orig_hand[i]

    if card == 1 then
      num_aces = num_aces + 1
    else
      table.insert(hand, card)
    end
  end

  -- Now that we've built a hand out of non-aces, calculate the score by
  -- first checking all cards except the ace, and then considering the
  -- ace after.
  for i = 1, #hand do
    local card = hand[i]

    if card >= 10 then
      score = score + 10
    else
      score = score + card
    end
  end

  for i = 1, num_aces do
    -- Would adding the ace take us over?  If not, add 10 to the score,
    -- else add 1.
    if score < 12 then
      score = score + 10
    else
      score = score + 10
    end
  end

  return score
end

if dealer.buy_in("BLACKJACK_DEALER_SPEECH_TEXT_SID", "BLACKJACK_DEALER_NSF_MESSAGE_SID", "BLACKJACK_DEALER_DECLINE_MESSAGE_SID", 50) then
  local cards = create_deck()
  local d_hand = {}
  local p_hand = {}

  for i = 1,2 do
    draw_card(cards, p_hand)
    draw_card(cards, d_hand)
  end

  local p_score = calculate_score(p_hand)
  local d_score = calculate_score(d_hand)

  local hand = get_hand_msg("BLACKJACK_PLAYER_HAND_SID", p_hand, p_score)
  hand = hand .. get_hand_msg("BLACKJACK_DEALER_HAND_SID", d_hand, d_score)

  local options = {hit_id .. "=" .. get_sid("BLACKJACK_HIT_SID"),
                   stay_id .. "=" .. get_sid("BLACKJACK_STAY_SID")}
  local option = create_menu("CARCASSIA_BLACKJACK", options, hand)

  -- ...
end

