#include "XMLBaseFeatureReader.hpp"
#include "Log.hpp"

using namespace std;

FeatureSymbolMap XMLBaseFeatureReader::get_feature_symbols(const XMLNode& base_features_node)
{
  FeatureSymbolMap fsm;
  map<string, ClassIdentifier> class_id_names = { {"GoodAltar", ClassIdentifier::CLASS_ID_GOOD_ALTAR},
                                                  {"NeutralAltar", ClassIdentifier::CLASS_ID_NEUTRAL_ALTAR},
                                                  {"EvilAltar", ClassIdentifier::CLASS_ID_EVIL_ALTAR},
                                                  {"Barrel", ClassIdentifier::CLASS_ID_BARREL},
                                                  {"Bench", ClassIdentifier::CLASS_ID_BENCH},
                                                  {"Bed", ClassIdentifier::CLASS_ID_BED},
                                                  {"Door", ClassIdentifier::CLASS_ID_DOOR},
                                                  {"Gate", ClassIdentifier::CLASS_ID_GATE},
                                                  {"DecorativeStatue", ClassIdentifier::CLASS_ID_DECORATIVE_STATUE},
                                                  {"HighPriestDecorativeStatue", ClassIdentifier::CLASS_ID_HIGH_PRIEST_DECORATIVE_STATUE},
                                                  {"KingDecorativeStatue", ClassIdentifier::CLASS_ID_KING_DECORATIVE_STATUE},
                                                  {"KnightDecorativeStatue", ClassIdentifier::CLASS_ID_KNIGHT_DECORATIVE_STATUE},
                                                  {"PetrifiedCorpseStatue", ClassIdentifier::CLASS_ID_PETRIFIED_CORPSE_STATUE},
                                                  {"QueenDecorativeStatue", ClassIdentifier::CLASS_ID_QUEEN_DECORATIVE_STATUE},
                                                  {"WarlordDecorativeStatue", ClassIdentifier::CLASS_ID_WARLORD_DECORATIVE_STATUE},
                                                  {"RegularDecorativeStatue", ClassIdentifier::CLASS_ID_REGULAR_STATUE},
                                                  {"SorcerorDecorativeStatue", ClassIdentifier::CLASS_ID_SORCEROR_DECORATIVE_STATUE},
                                                  {"EastWestPew", ClassIdentifier::CLASS_ID_EAST_WEST_PEW},
                                                  {"FirePillar", ClassIdentifier::CLASS_ID_FIRE_PILLAR},
                                                  {"Forge", ClassIdentifier::CLASS_ID_FORGE},
                                                  {"Kiln", ClassIdentifier::CLASS_ID_KILN},
                                                  {"Fountain", ClassIdentifier::CLASS_ID_FOUNTAIN},
                                                  {"JewelerWorkbench", ClassIdentifier::CLASS_ID_JEWELER_WORKBENCH},
                                                  {"Pew", ClassIdentifier::CLASS_ID_PEW},
                                                  {"Pulper", ClassIdentifier::CLASS_ID_PULPER},
                                                  {"Sarcophagus", ClassIdentifier::CLASS_ID_SARCOPHAGUS},
                                                  {"Sign", ClassIdentifier::CLASS_ID_SIGN},
                                                  {"SlotMachine", ClassIdentifier::CLASS_ID_SLOT_MACHINE},
                                                  {"StoneMarker", ClassIdentifier::CLASS_ID_STONE_MARKER},
                                                  {"Table", ClassIdentifier::CLASS_ID_TABLE},
                                                  {"Tannery", ClassIdentifier::CLASS_ID_TANNERY},
                                                  {"Trap", ClassIdentifier::CLASS_ID_TRAP},
                                                  {"WheelAndLoom", ClassIdentifier::CLASS_ID_WHEEL_AND_LOOM} };

  Log& log = Log::instance();
  for (auto cid_pair : class_id_names)
  {
    string node_name = cid_pair.first;
    XMLNode base_feature_node = XMLUtils::get_next_element_by_local_name(base_features_node, node_name);

    if (!base_feature_node.is_null())
    {
      Symbol s = get_feature_symbol(base_feature_node);
      fsm[cid_pair.second] = s;
    }
    else
    {
      log.error("Could not find base feature node " + cid_pair.first + "!");
    }
  }

  return fsm;
}

Symbol XMLBaseFeatureReader::get_feature_symbol(const XMLNode& base_feature_node)
{
  Symbol s('?', Colour::COLOUR_WHITE);

  if (!base_feature_node.is_null())
  {
    XMLNode symbol_node = XMLUtils::get_next_element_by_local_name(base_feature_node, "Symbol");
    parse_symbol(s, symbol_node);
  }

  return s;
}
