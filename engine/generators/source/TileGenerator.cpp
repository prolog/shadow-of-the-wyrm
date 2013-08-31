#include <boost/make_shared.hpp>
#include "Game.hpp"
#include "Log.hpp"
#include "TileConfigurationFactory.hpp"
#include "TileGenerator.hpp"
#include "ItemManager.hpp"
#include "tiles.hpp"
#include "AllTiles.hpp"

TilePtr TileGenerator::generate(const TileType& tile_type, const TileType& subtile_type, const bool generate_random_items)
{
  // To make it easier to remember what needs to be updated:
  BOOST_STATIC_ASSERT(TILE_TYPE_LAST == 42);

  TilePtr result_tile;

  switch(tile_type)
  {
    case TILE_TYPE_UNDEFINED:
      Log::instance().log("Attempting to generate an undefined tile type");
      break;
    case TILE_TYPE_FIELD:
      result_tile = boost::make_shared<FieldTile>();
      break;
    case TILE_TYPE_SCRUB:
      result_tile = boost::make_shared<ScrubTile>();
      break;
    case TILE_TYPE_WHEAT:
      result_tile = boost::make_shared<WheatTile>();
      break;
    case TILE_TYPE_CAIRN:
      result_tile = boost::make_shared<CairnTile>();
      break;
    case TILE_TYPE_TREE:
      result_tile = boost::make_shared<TreeTile>();
      break;      
    case TILE_TYPE_DESERT:
      result_tile = boost::make_shared<DesertTile>();
      break;
    case TILE_TYPE_ROAD:
      result_tile = boost::make_shared<RoadTile>();
      break;
    case TILE_TYPE_RIVER:
      result_tile = boost::make_shared<RiverTile>();
      break;
    case TILE_TYPE_SEA:
      result_tile = boost::make_shared<SeaTile>();
      break;
    case TILE_TYPE_SHOALS:
      result_tile = boost::make_shared<ShoalsTile>();
      break;
    case TILE_TYPE_DUNGEON:
      result_tile = boost::make_shared<DungeonTile>();
      break;
    case TILE_TYPE_ROCK:
      result_tile = boost::make_shared<RockTile>();
      break;
    case TILE_TYPE_BARROW:
      result_tile = boost::make_shared<BarrowTile>();
      break;
    case TILE_TYPE_GRAVE:
      result_tile = boost::make_shared<GraveTile>();
      break;
    case TILE_TYPE_MARSH:
      result_tile = boost::make_shared<MarshTile>();
      break;
    case TILE_TYPE_REEDS:
      result_tile = boost::make_shared<ReedsTile>();
      break;
    case TILE_TYPE_HILLS:
      result_tile = boost::make_shared<HillsTile>();
      break;
    case TILE_TYPE_MOUNTAINS:
      result_tile = boost::make_shared<MountainsTile>();
      break;
    case TILE_TYPE_BEACH:
      result_tile = boost::make_shared<BeachTile>();
      break;
    case TILE_TYPE_BUSH:
      result_tile = boost::make_shared<BushTile>();
      break;
    case TILE_TYPE_WEEDS:
      result_tile = boost::make_shared<WeedsTile>();
      break;
    case TILE_TYPE_SPRINGS:
      result_tile = boost::make_shared<SpringsTile>();
      break;
    case TILE_TYPE_FOREST:
      result_tile = boost::make_shared<ForestTile>();
      break;
    case TILE_TYPE_UP_STAIRCASE:
      result_tile = boost::make_shared<UpStaircaseTile>();
      break;
    case TILE_TYPE_DOWN_STAIRCASE:
      result_tile = boost::make_shared<DownStaircaseTile>();
      break;
    case TILE_TYPE_CAVERN:
      result_tile = boost::make_shared<CavernTile>();
      break;
    case TILE_TYPE_VILLAGE:
      result_tile = boost::make_shared<VillageTile>(subtile_type);
      break;
    case TILE_TYPE_DUNGEON_COMPLEX:
      result_tile = boost::make_shared<DungeonComplexTile>();
      break;
    case TILE_TYPE_BARRACKS:
      result_tile = boost::make_shared<BarracksTile>();
      break;
    case TILE_TYPE_CASTLE:
      result_tile = boost::make_shared<CastleTile>();
      break;
    case TILE_TYPE_CHURCH:
      result_tile = boost::make_shared<ChurchTile>(subtile_type);
      break;
    case TILE_TYPE_GRAVEYARD:
      result_tile = boost::make_shared<GraveyardTile>();
      break;
    case TILE_TYPE_KEEP:
      result_tile = boost::make_shared<KeepTile>();
      break;
    case TILE_TYPE_LIBRARY:
      result_tile = boost::make_shared<LibraryTile>();
      break;
    case TILE_TYPE_SITE_OF_DEATH:
      result_tile = boost::make_shared<SiteOfDeathTile>(subtile_type);
      break;
    case TILE_TYPE_TEMPLE:
      result_tile = boost::make_shared<TempleTile>(subtile_type);
      break;
    case TILE_TYPE_DAIS:
      result_tile = boost::make_shared<DaisTile>();
      break;
    case TILE_TYPE_PIER:
      result_tile = boost::make_shared<PierTile>();
      break;
    case TILE_TYPE_WILD_ORCHARD:
      result_tile = boost::make_shared<WildOrchardTile>();
      break;
    case TILE_TYPE_FRUIT_TREE:
      result_tile = boost::make_shared<FruitTreeTile>();
      break;
    case TILE_TYPE_EVERGREEN_TREE:
      result_tile = boost::make_shared<EvergreenTreeTile>();
      break;
    case TILE_TYPE_ROCKY_EARTH:
      result_tile = boost::make_shared<RockyEarthTile>();
      break;
    default:
      break;
  }

  if (generate_random_items)
  {
    configure_tile(result_tile);
  }

  // The tile shouldn't be null after generation!
  BOOST_ASSERT(result_tile);

  return result_tile;
}

void TileGenerator::configure_tile(TilePtr result_tile)
{
  Season season = SEASON_SUMMER;
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
    case ALIGNMENT_RANGE_EVIL:
      worship_site = boost::make_shared<SiteOfDeathTile>(TILE_TYPE_FIELD);
      break;
    case ALIGNMENT_RANGE_GOOD:
      worship_site = boost::make_shared<ChurchTile>(TILE_TYPE_FIELD);
      break;
    case ALIGNMENT_RANGE_NEUTRAL:
    default:
      worship_site = boost::make_shared<TempleTile>(TILE_TYPE_FIELD);
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
    case STAIRCASE_UP:
      result_tile = boost::make_shared<UpStaircaseTile>();
      break;
    case STAIRCASE_DOWN:
      result_tile = boost::make_shared<DownStaircaseTile>();
      break;
    default:
      break;
  }

  return result_tile;
}

#ifdef UNIT_TESTS
#include "unit_tests/TileGenerator_test.cpp"
#endif
