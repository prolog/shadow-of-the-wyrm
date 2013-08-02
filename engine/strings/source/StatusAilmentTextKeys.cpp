#include "Creature.hpp"
#include "StatusAilmentTextKeys.hpp"

using namespace std;

// Status ailment text keys:
const string StatusAilmentTextKeys::STATUS_HUNGER_STUFFED          = "STATUS_HUNGER_STUFFED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_STUFFED  = "STATUS_MESSAGE_HUNGER_STUFFED";
const string StatusAilmentTextKeys::STATUS_HUNGER_FULL             = "STATUS_HUNGER_FULL";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_FULL     = "STATUS_MESSAGE_HUNGER_FULL";
const string StatusAilmentTextKeys::STATUS_HUNGER_NORMAL           = "STATUS_HUNGER_NORMAL";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_NORMAL   = "STATUS_MESSAGE_HUNGER_NORMAL";
const string StatusAilmentTextKeys::STATUS_HUNGER_HUNGRY           = "STATUS_HUNGER_HUNGRY";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_HUNGRY   = "STATUS_MESSAGE_HUNGER_HUNGRY";
const string StatusAilmentTextKeys::STATUS_HUNGER_STARVING         = "STATUS_HUNGER_STARVING";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_STARVING = "STATUS_MESSAGE_HUNGER_STARVING";
const string StatusAilmentTextKeys::STATUS_HUNGER_DYING            = "STATUS_HUNGER_DYING";
const string StatusAilmentTextKeys::STATUS_MESSAGE_HUNGER_DYING    = "STATUS_MESSAGE_HUNGER_DYING";

const string StatusAilmentTextKeys::STATUS_POISON = "STATUS_POISON";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISONED = "STATUS_MESSAGE_PLAYER_POISONED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_POISON_CURED = "STATUS_MESSAGE_PLAYER_POISON_CURED";

const string StatusAilmentTextKeys::STATUS_MUTE = "STATUS_MUTE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTED = "STATUS_MESSAGE_PLAYER_MUTED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_MUTENESS_CURED = "STATUS_MESSAGE_PLAYER_MUTENESS_CURED";

const string StatusAilmentTextKeys::STATUS_PARALYSIS = "STATUS_PARALYSIS";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYZED = "STATUS_MESSAGE_PLAYER_PARALYZED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_PARALYSIS_CURED = "STATUS_MESSAGE_PLAYER_PARALYSIS_CURED";

const string StatusAilmentTextKeys::STATUS_SLOWNESS = "STATUS_SLOWNESS";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SLOWED = "STATUS_MESSAGE_PLAYER_SLOWED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_SLOWNESS_CURED = "STATUS_MESSAGE_PLAYER_SLOWNESS_CURED";

const string StatusAilmentTextKeys::STATUS_HASTE = "STATUS_HASTE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_HASTED = "STATUS_MESSAGE_PLAYER_HASTED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_HASTE_DONE = "STATUS_MESSAGE_PLAYER_HASTE_DONE";

const string StatusAilmentTextKeys::STATUS_STONE = "STATUS_STONE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE = "STATUS_MESSAGE_PLAYER_STONE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_STONE_CURED = "STATUS_MESSAGE_PLAYER_STONE_CURED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_STONE_FINALIZE = "STATUS_MESSAGE_STONE_FINALIZE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_STONE_CRUMBLE = "STATUS_MESSAGE_CORPSE_CRUMBLE";

const string StatusAilmentTextKeys::STATUS_BLOODIED = "STATUS_BLOODIED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLOODIED = "STATUS_MESSAGE_PLAYER_BLOODIED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_PLAYER_BLOODIED_CURED = "STATUS_MESSAGE_PLAYER_BLOODIED_CURED";

// public functions
const string StatusAilmentTextKeys::get_npc_poisoned_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_POISONED);
}

const string StatusAilmentTextKeys::get_npc_undo_poison_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_POISON);
}

const string StatusAilmentTextKeys::get_npc_muted_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_MUTED);
}

const string StatusAilmentTextKeys::get_npc_undo_muteness_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_MUTENESS);
}

const string StatusAilmentTextKeys::get_npc_paralyzed_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_PARALYZED);
}

const string StatusAilmentTextKeys::get_npc_undo_paralysis_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_PARALYSIS);
}

const string StatusAilmentTextKeys::get_npc_slowed_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_SLOWED);
}

const string StatusAilmentTextKeys::get_npc_undo_slowness_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_SLOWNESS);
}

const string StatusAilmentTextKeys::get_npc_hasted_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_HASTED);
}

const string StatusAilmentTextKeys::get_npc_undo_haste_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_HASTE);
}

const string StatusAilmentTextKeys::get_npc_stone_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_STONE);
}

const string StatusAilmentTextKeys::get_npc_undo_stone_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_STONE);
}

const string StatusAilmentTextKeys::get_npc_bloodied_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_BLOODIED);
}

const string StatusAilmentTextKeys::get_npc_undo_bloodied_message(CreaturePtr creature)
{
  return get_general_npc_message(creature->get_description_sid(), StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_BLOODIED);
}

// Protected
const string StatusAilmentTextKeys::get_general_npc_message(const string& npc_sid, const string& message_sid)
{
  string npc = StringTable::get(npc_sid);
  string message = StringTable::get(message_sid);

  boost::replace_first(message, "%s", npc);
  message[0] = toupper(message[0]);

  return message;
}

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_POISONED = "STATUS_MESSAGE_NPC_POISONED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_POISON = "STATUS_MESSAGE_NPC_UNDO_POISON";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_MUTED = "STATUS_MESSAGE_NPC_MUTED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_MUTENESS = "STATUS_MESSAGE_NPC_UNDO_MUTENESS";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_PARALYZED = "STATUS_MESSAGE_NPC_PARALYZED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_PARALYSIS = "STATUS_MESSAGE_NPC_UNDO_PARALYSIS";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_SLOWED = "STATUS_MESSAGE_NPC_SLOWED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_SLOWNESS = "STATUS_MESSAGE_NPC_UNDO_SLOWNESS";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_HASTED = "STATUS_MESSAGE_NPC_HASTED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_HASTE = "STATUS_MESSAGE_NPC_UNDO_HASTE";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_STONE = "STATUS_MESSAGE_NPC_STONE";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_STONE = "STATUS_MESSAGE_NPC_UNDO_STONE";

const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_BLOODIED = "STATUS_MESSAGE_NPC_BLOODIED";
const string StatusAilmentTextKeys::STATUS_MESSAGE_NPC_UNDO_BLOODIED = "STATUS_MESSAGE_NPC_UNDO_BLOODIED";
