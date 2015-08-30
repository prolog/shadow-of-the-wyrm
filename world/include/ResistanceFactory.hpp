#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Resistances.hpp"

using ResistancesSerializationMap = std::map<ClassIdentifier, std::shared_ptr<Resistance>>;

class ResistanceFactory
{
  public:
    static std::shared_ptr<Resistance> create_resistance(const ClassIdentifier clid);

  protected:
    ResistanceFactory();
    ~ResistanceFactory();

    static void initialize_resistances_map();

    static ResistancesSerializationMap resistances_map;
};

