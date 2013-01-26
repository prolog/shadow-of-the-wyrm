#pragma once
#include "IMapTypeQuery.hpp"
#include "MapTypes.hpp"

class MapTypeQueryFactory
{
  public:
    static IMapTypeQueryPtr create_map_type_query(const MapType map_type);
  protected:
    MapTypeQueryFactory();
    ~MapTypeQueryFactory();
};

