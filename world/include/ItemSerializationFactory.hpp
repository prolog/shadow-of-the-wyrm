#pragma once
#include <map>
#include "ClassIdentifiers.hpp"
#include "Item.hpp"

using ItemSerializationMap = std::map<ClassIdentifier, ItemPtr>;

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

