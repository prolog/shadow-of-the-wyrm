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
    case MapType::MAP_TYPE_UNDERWATER:
    case MapType::MAP_TYPE_UNDERWORLD:
    case MapType::MAP_TYPE_AIR:
      mtq = std::make_unique<DepthMapTypeQuery>();
      break;
    case MapType::MAP_TYPE_WORLD:
    case MapType::MAP_TYPE_COSMOS:
    case MapType::MAP_TYPE_OVERWORLD:
    default:
      mtq = std::make_unique<DepthlessMapTypeQuery>();
      break;
  }

  return mtq;
}

