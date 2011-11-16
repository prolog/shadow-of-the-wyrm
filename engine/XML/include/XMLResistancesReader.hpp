#pragma once

class Resistances;
class XMLNode;

class XMLResistancesReader
{
  public:
    Resistances get_resistances(const XMLNode& node);

  protected:
    void parse_resistances(Resistances& resistances, const XMLNode& resistances_node);
};
