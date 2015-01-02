#pragma once

enum struct HitTypeEnum
{
  HIT_TYPE_REGULAR = 0,
  HIT_TYPE_MIGHTY = 1,
  HIT_TYPE_CRITICAL = 2
};

class HitTypeEnumConverter
{
  public:
    static HitTypeEnum from_successful_to_hit_roll(const int to_hit);

  protected:
    HitTypeEnumConverter();
};
