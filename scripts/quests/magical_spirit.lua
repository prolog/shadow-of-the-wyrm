require('constants')

local spells = {"c_04_blink", "c_06_purify", "d_04_divine_wind", 
                "d_07_soften", "a_03_lightning_bolt", "a_07_fireball",
                "m_06_haste", "m_07_slow", "p_03_cloak_of_shadows",
                "p_04_nether_bolt"}

local spell1 = table.remove(spells, RNG_range(1, table.getn(spells)))
local spell2 = table.remove(spells, RNG_range(1, table.getn(spells)))

add_spell_castings(PLAYER_ID, spell1, RNG_range(2, 5))
add_spell_castings(PLAYER_ID, spell2, RNG_range(2, 5))

add_message_with_pause("MAGICAL_SPIRIT_SPELLS_SID")
clear_and_add_message("MAGICAL_SPIRIT_SPELLS2_SID")

local spirit_id = args[SPEAKING_CREATURE_ID]
remove_creature_from_map(spirit_id) 
