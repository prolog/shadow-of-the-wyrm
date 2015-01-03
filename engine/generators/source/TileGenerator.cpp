#include "Game.hpp"
#include "Log.hpp"
#include "TileConfigurationFactory.hpp"
#include "TileGenerator.hpp"
#include "ItemManager.hpp"
#include "tiles.hpp"
#include "AllTiles.hpp"

TileGenerator::TileGenerator()
: generate_items(true)
{
}

TileGenerator::TileGenerator(const bool generate)
: generate_items(generate)
{
}

void TileGenerator::set_generate_items(const bool new_generate_items)
{
  generate_items = new_generate_items;
}

bool TileGenerator::get_generate_items() const
{
  return generate_items;
}

TilePtr TileGenerator::generate(const TileType& tile_type, const TileType& subtile_type)
{
  // To make it easier to remember what needs to be updated:
  static_assert(TileType::TILE_TYPE_LAST == TileType(46), "Unexpected TileType::TILE_TYPE_LAST value.");

  TilePtr result_tile;

  switch(tile_type)
  {
    case TileType::TILE_TYPE_UNDEFINED:
      Log::instance().log("TileGenerator::generate - Attempting to generate an undefined tile type");
      break;
    case TileType::TILE_TYPE_FIELD:
      result_tile = std::make_shared<FieldTile>();
      break;
    case TileType::TILE_TYPE_SCRUB:
      result_tile = std::make_shared<ScrubTile>();
      break;
    case TileType::TILE_TYPE_WHEAT:
      result_tile = std::make_shared<WheatTile>();
      break;
    case TileType::TILE_TYPE_CAIRN:
      result_tile = std::make_shared<CairnTile>();
      break;
    case TileType::TILE_TYPE_TREE:
      result_tile = std::make_shared<TreeTile>();
      break;      
    case TileType::TILE_TYPE_DESERT:
      result_tile = std::make_shared<DesertTile>();
      break;
    case TileType::TILE_TYPE_ROAD:
      result_tile = std::make_shared<RoadTile>();
      break;
    case TileType::TILE_TYPE_RIVER:
      result_tile = std::make_shared<RiverTile>();
      break;
    case TileType::TILE_TYPE_SEA:
      result_tile = std::make_shared<SeaTile>();
      break;
    case TileType::TILE_TYPE_SHOALS:
      result_tile = std::make_shared<ShoalsTile>();
      break;
    case TileType::TILE_TYPE_DUNGEON:
      result_tile = std::make_shared<DungeonTile>();
      break;
    case TileType::TILE_TYPE_ROCK:
      result_tile = std::make_shared<RockTile>();
      break;
    case TileType::TILE_TYPE_BARROW:
      result_tile = std::make_shared<BarrowTile>();
      break;
    case TileType::TILE_TYPE_GRAVE:
      result_tile = std::make_shared<GraveTile>();
      break;
    case TileType::TILE_TYPE_MARSH:
      result_tile = std::make_shared<MarshTile>();
      break;
    case TileType::TILE_TYPE_REEDS:
      result_tile = std::make_shared<ReedsTile>();
      break;
    case TileType::TILE_TYPE_HILLS:
      result_tile = std::make_shared<HillsTile>();
      break;
    case TileType::TILE_TYPE_MOUNTAINS:
      result_tile = std::make_shared<MountainsTile>();
      break;
    case TileType::TILE_TYPE_BEACH:
      result_tile = std::make_shared<BeachTile>();
      break;
    case TileType::TILE_TYPE_BUSH:
      result_tile = std::make_shared<BushTile>();
      break;
    case TileType::TILE_TYPE_WEEDS:
      result_tile = std::make_shared<WeedsTile>();
      break;
    case TileType::TILE_TYPE_SPRINGS:
      result_tile = std::make_shared<SpringsTile>();
      break;
    case TileType::TILE_TYPE_FOREST:
      result_tile = std::make_shared<ForestTile>();
      break;
    case TileType::TILE_TYPE_UP_STAIRCASE:
      result_tile = std::make_shared<UpStaircaseTile>();
      break;
    case TileType::TILE_TYPE_DOWN_STAIRCASE:
      result_tile = std::make_shared<DownStaircaseTile>();
      break;
    case TileType::TILE_TYPE_CAVERN:
      result_tile = std::make_shared<CavernTile>();
      break;
    case TileType::TILE_TYPE_VILLAGE:
      result_tile = std::make_shared<VillageTile>(subtile_type);
      break;
    case TileType::TILE_TYPE_DUNGEON_COMPLEX:
      result_tile = std::make_shared<DungeonComplexTile>();
      break;
    case TileType::TILE_TYPE_BARRACKS:
      result_tile = std::make_shared<BarracksTile>();
      break;
    case TileType::TILE_TYPE_CASTLE:
      result_tile = std::make_shared<CastleTile>();
      break;
    case TileType::TILE_TYPE_CHURCH:
      result_tile = std::make_shared<ChurchTile>(subtile_type);
      break;
    case TileType::TILE_TYPE_GRAVEYARD:
      result_tile = std::make_shared<GraveyardTile>();
      break;
    case TileType::TILE_TYPE_KEEP:
      result_tile = std::make_shared<KeepTile>();
      break;
    case TileType::TILE_TYPE_LIBRARY:
      result_tile = std::make_shared<LibraryTile>();
      break;
    case TileType::TILE_TYPE_SITE_OF_DEATH:
      result_tile = std::make_shared<SiteOfDeathTile>(subtile_type);
      break;
    case TileType::TILE_TYPE_TEMPLE:
      result_tile = std::make_shared<TempleTile>(subtile_type);
      break;
    case TileType::TILE_TYPE_DAIS:
      result_tile = std::make_shared<DaisTile>();
      break;
    case TileType::TILE_TYPE_PIER:
      result_tile = std::make_shared<PierTile>();
      break;
    case TileType::TILE_TYPE_WILD_ORCHARD:
      result_tile = std::make_shared<WildOrchardTile>();
      break;
    case TileType::TILE_TYPE_FRUIT_TREE:
      result_tile = std::make_shared<FruitTreeTile>();
      break;
    case TileType::TILE_TYPE_EVERGREEN_TREE:
      result_tile = std::make_shared<EvergreenTreeTile>();
      break;
    case TileType::TILE_TYPE_ROCKY_EARTH:
      result_tile = std::make_shared<RockyEarthTile>();
      break;
    case TileType::TILE_TYPE_MINE:
      result_tile = std::make_shared<MineTile>();
      break;
    case TileType::TILE_TYPE_WELL:
      result_tile = std::make_shared<WellTile>();
      break;
    case TileType::TILE_TYPE_CRYPT:
      result_tile = std::make_shared<CryptTile>();
      break;
    case TileType::TILE_TYPE_AIR:
      result_tile = std::make_shared<AirTile>();
    default:
      break;
  }

  if (generate_items)
  {
    configure_tile(result_tile);
  }

  // The tile shouldn't be null after generation!
  BOOST_ASSERT(result_tile);

  return result_tile;
}

void TileGenerator::configure_tile(TilePtr result_tile)
{
  Season season = Season::SEASON_SUMMER;
  Game& game = Game::instance();
  WorldPtr world = game.get_current_world();

  if (world)
  {
    ISeasonPtr seasonp = world->get_calendar().get_season();
      
    if (seasonp)
    {
      season = seasonp->get_season();
    }
  }

  TileConfigurationFactory tile_config_factory;
  ITileConfigurationPtr tile_config = tile_config_factory.create_tile_configuration(result_tile->get_tile_type());

  if (tile_config)
  {
    tile_config->configure(result_tile, season);
  }
}

// Generate an appropriate worship site, based on the given
// alignment:
// - Good: Churches
// - Neutral: Temples
// - Evil: Sacrifice Sites
//
// These are only ever generated on the world map, so ITileConfigurationPtrs
// are not needed.
WorshipSiteTilePtr TileGenerator::generate_worship_site_tile(const AlignmentRange alignment, const std::string& deity_id, const WorshipSiteType worship_site_type)
{
  std::string s_did = deity_id;
  WorshipSiteTilePtr worship_site;
  
  switch(alignment)
  {
    // JCD FIXME: At some point, it'll be worth making the tile subtype
    // a variable.  But for now, I just want a pretty world.
    case AlignmentRange::ALIGNMENT_RANGE_EVIL:
      worship_site = std::make_shared<SiteOfDeathTile>(TileType::TILE_TYPE_FIELD);
      break;
    case AlignmentRange::ALIGNMENT_RANGE_GOOD:
      worship_site = std::make_shared<ChurchTile>(TileType::TILE_TYPE_FIELD);
      break;
    case AlignmentRange::ALIGNMENT_RANGE_NEUTRAL:
    default:
      worship_site = std::make_shared<TempleTile>(TileType::TILE_TYPE_FIELD);
      break;
  }
  
  if (worship_site)
  {
    worship_site->set_deity_id(deity_id);
    worship_site->set_worship_site_type(worship_site_type);
  }
  
  return worship_site;
}

StaircaseTilePtr TileGenerator::generate_staircase(const StaircaseType& staircase_type)
{
  StaircaseTilePtr result_tile;

  switch(staircase_type)
  {
    case StaircaseType::STAIRCASE_UP:
      result_tile = std::make_shared<UpStaircaseTile>();
      break;
    case StaircaseType::STAIRCASE_DOWN:
      result_tile = std::make_shared<DownStaircaseTile>();
      break;
    default:
      break;
  }

  return result_tile;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileGenerator_test.cpp"
#endif
