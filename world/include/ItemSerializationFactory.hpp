#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Item.hpp"

typedef std::map<ClassIdentifier, ItemPtr> ItemSerializationMap;

class ItemSerializationFactory
{
  public:
    static ItemPtr create_item(const ClassIdentifier ci);

  protected:
    ItemSerializationFactory();
    ~ItemSerializationFactory();

    static void initialize_item_map();

    static ItemSerializationMap item_map;
};

