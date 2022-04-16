#pragma once
#include <string>

class SettlementTextKeys
{
  public:
    static const std::string SETTLEMENT_NAME_ADJECTIVES;
    static const std::string SETTLEMENT_NAME_DESCRIPTIONS;
    static const std::string SETTLEMENT_NAME_SINGLE_PREFIX;
    static const std::string SETTLEMENT_NAME_SINGLE_SUFFIX;

    // %s1 = adjective, %s2 = description/feature
    static const std::string DESCRIPTIVE_SETTLEMENT_FORMAT;

    // %s1 = name, %s2 = description/feature
    static const std::string POSSESSIVE_SETTLEMENT_FORMAT;

    // Located settlement formats give names reminiscent
    // of English places: X-upon-Y, etc.  They each
    // follow a %s1-<something>-%s2 format.
    static const std::string LOCATED_SETTLEMENT_FORMATS;

    // Single settlement names are of the form x-wood,
    // y-field, etc.
    static const std::string SINGLE_SETTLEMENT_FORMAT;

  protected:
    SettlementTextKeys();
    ~SettlementTextKeys();
};
