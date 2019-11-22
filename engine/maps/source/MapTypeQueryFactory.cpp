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
    case MapType::MAP_TYPE_UNDERWORLD:
      mtq = std::make_unique<UnderworldMapTypeQuery>();
      break;
    case MapType::MAP_TYPE_WORLD:
    case MapType::MAP_TYPE_OVERWORLD:
    default:
      mtq = std::make_unique<OverworldMapTypeQuery>();
      break;
  }

  return mtq;
}

