#pragma once
class StatisticsModifier;
class XMLNode;

class XMLStatisticsModifierReader
{
  public:
    XMLStatisticsModifierReader();
    ~XMLStatisticsModifierReader();

    StatisticsModifier get_statistics_modifier(const XMLNode& statistics_modifiers_node);
};
