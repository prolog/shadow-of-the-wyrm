require('constants')
require('merchant_common')

local sw_cost = 50

merchant_common.chat(PLAYER_ID, SILVERWEED_ID, sw_cost, "HERBALIST_OFFER_SID", "HERBALIST_ACCEPT_SID", "HERBALIST_DECLINE_SID", "HERBALIST_INSUFFICIENT_FUNDS_SID")
