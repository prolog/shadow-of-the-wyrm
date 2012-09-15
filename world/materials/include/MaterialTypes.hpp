#pragma once

enum MaterialType
{
  MATERIAL_TYPE_CLOTH = 0,
  MATERIAL_TYPE_DRAGON_SCALE = 1,
  MATERIAL_TYPE_GLASS = 2,
  MATERIAL_TYPE_IRON = 3,
  MATERIAL_TYPE_LEATHER = 4,
  MATERIAL_TYPE_PAPER = 5,
  MATERIAL_TYPE_STEEL = 6,
  MATERIAL_TYPE_STONE = 7,
  MATERIAL_TYPE_WOOD = 8,
  MATERIAL_TYPE_MARBLE = 9,
  MATERIAL_TYPE_ONYX = 10,
  MATERIAL_TYPE_IVORY = 11
};

inline MaterialType operator--(MaterialType &mt, int)
{
  return mt = MaterialType(mt-1);
}

inline MaterialType operator++(MaterialType &mt, int)
{
  return mt = MaterialType(mt+1);
}

