#pragma once

enum EquipmentWornLocation
{
  EQUIPMENT_WORN_NONE = -1,
  EQUIPMENT_WORN_HEAD = 0,
  EQUIPMENT_WORN_NECK = 1,
  EQUIPMENT_WORN_LEFT_HAND = 2,
  EQUIPMENT_WORN_RIGHT_HAND = 3,
  EQUIPMENT_WORN_BODY = 4,
  EQUIPMENT_WORN_ABOUT_BODY = 5,
  EQUIPMENT_WORN_LEFT_FINGER = 6,
  EQUIPMENT_WORN_RIGHT_FINGER = 7,
  EQUIPMENT_WORN_FEET = 8,
  EQUIPMENT_WORN_LAST = 9
};

inline EquipmentWornLocation operator--(EquipmentWornLocation &ewl, int)
{
  return ewl = EquipmentWornLocation(ewl-1);
}

inline EquipmentWornLocation operator++(EquipmentWornLocation &ewl, int)
{
  return ewl = EquipmentWornLocation(ewl+1);
}

