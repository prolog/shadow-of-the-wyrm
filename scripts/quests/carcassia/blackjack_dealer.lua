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
local function get_hand_synopsis(base_sid, cards)
  msg = get_sid(base_sid)

  for k,v in ipairs(cards) do
    msg = msg .. get_card_value(v)

    if k ~= #cards then
      msg = msg .. ", "
    end
  end

  msg = msg .. ". "

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

if dealer.buy_in("BLACKJACK_DEALER_SPEECH_TEXT_SID", "BLACKJACK_DEALER_NSF_MESSAGE_SID", "BLACKJACK_DEALER_DECLINE_MESSAGE_SID", 50) then
  local cards = create_deck()
  local d_hand = {}
  local p_hand = {}

  for i = 1,2 do
    draw_card(cards, p_hand)
    draw_card(cards, d_hand)
  end

  local hand = get_hand_synopsis("BLACKJACK_PLAYER_HAND_SID", p_hand)
  hand = hand .. get_hand_synopsis("BLACKJACK_DEALER_HAND_SID", d_hand)

  local options = {hit_id .. "=" .. get_sid("BLACKJACK_HIT_SID"),
                   stay_id .. "=" .. get_sid("BLACKJACK_STAY_SID")}
  local option = create_menu("CARCASSIA_BLACKJACK", options, hand)

  -- ...
end

