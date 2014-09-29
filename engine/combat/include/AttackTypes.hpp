#pragma once

enum AttackType
{
  ATTACK_TYPE_MELEE_PRIMARY = 0,
  ATTACK_TYPE_MELEE_SECONDARY = 1,
  ATTACK_TYPE_RANGED = 2,
  ATTACK_TYPE_MAGICAL = 3,
  // Used for attacks like kicking, etc., which are always unarmed and make 
  // no use of anything in the inventory or equipment.
  ATTACK_TYPE_MELEE_TERTIARY_UNARMED = 4 
};
