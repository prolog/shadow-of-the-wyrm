#pragma once
#include <string>

class SkinningConstants
{
  public:
    static const std::string SKIN_ID; 
    static const std::string SKIN_DESCRIPTION_SID; 
  	static const std::string SKIN_USAGE_DESCRIPTION_SID;
    static const std::string SKIN_SOAK;
    static const int SKIN_ENCHANT_PCT_CHANCE_SOAK;

  protected:
    SkinningConstants();
    ~SkinningConstants();
};
