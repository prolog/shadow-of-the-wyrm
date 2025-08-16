#pragma once
#include <string>

class SkinningConstants
{
  public:
    static const std::string SKIN_ID; 
    static const std::string SKIN_IS_SKIN;
    static const std::string SKIN_BONES_DESCRIPTION_SID; 
  	static const std::string SKIN_BONES_USAGE_DESCRIPTION_SID;
    static const std::string SKIN_SOAK;
    static const int SKIN_ENCHANT_PCT_CHANCE_SOAK;
    static const std::string CORPSE_BONES_ID;

  protected:
    SkinningConstants();
    ~SkinningConstants();
};
