#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Resistances.hpp"

typedef std::map<ClassIdentifier, boost::shared_ptr<Resistance> > ResistancesSerializationMap;

class ResistanceFactory
{
  public:
    static boost::shared_ptr<Resistance> create_resistance(const ClassIdentifier clid);

  protected:
    ResistanceFactory();
    ~ResistanceFactory();

    static void initialize_resistances_map();

    static ResistancesSerializationMap resistances_map;
};

