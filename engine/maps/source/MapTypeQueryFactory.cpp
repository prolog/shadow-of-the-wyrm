#include "MapTypeQueryFactory.hpp"
#include "MapTypeQueries.hpp"

MapTypeQueryFactory::MapTypeQueryFactory()
{
}

MapTypeQueryFactory::~MapTypeQueryFactory()
{
}

IMapTypeQueryPtr MapTypeQueryFactory::create_map_type_query(const MapType map_type)
{
  IMapTypeQueryPtr mtq;

  switch(map_type)
  {
    case MAP_TYPE_UNDERWORLD:
      mtq = std::make_shared<UnderworldMapTypeQuery>();
      break;
    case MAP_TYPE_WORLD:
    case MAP_TYPE_OVERWORLD:
    default:
      mtq = std::make_shared<OverworldMapTypeQuery>();
      break;
  }

  return mtq;
}

