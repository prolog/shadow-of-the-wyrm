#pragma once
#include <string>

class SettlementTextKeys
{
  public:
    static const std::string SETTLEMENT_NAME_ADJECTIVES;
    static const std::string SETTLEMENT_NAME_DESCRIPTIONS;

    // %s1 = adjective, %s2 = description/feature
    static const std::string DESCRIPTIVE_SETTLEMENT_FORMAT;

    // %s1 = name, %s2 = description/feature
    static const std::string POSSESSIVE_SETTLEMENT_FORMAT;
  protected:
    SettlementTextKeys();
    ~SettlementTextKeys();
};
