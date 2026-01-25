#pragma once
#include "Tile.hpp"
#include "IMessageManager.hpp"

// TileDamageProcessor is responsible for applying a particular damage
// type to a tile.  In practical terms, this involves checking to see if
// any items are potentially destroyed, checking to see whether they're
// actually destroyed, and then destroying them.
class TileDamageProcessor
{
  public:
    void process(MapPtr map, TilePtr tile, CreaturePtr creature);
    virtual ~TileDamageProcessor() = default;

  protected:
    virtual bool destroy_item() const;
    virtual void process_item(ItemPtr item);
    virtual std::string get_message_sid() const;
    virtual int get_pct_chance() const;
    
    virtual bool affects_item(ItemPtr item);
    virtual bool affects_feature(FeaturePtr feature);
    virtual bool affects_material(const MaterialType mt) = 0;

    virtual void process_feature(CreaturePtr creature, MapPtr map, TilePtr tile, FeaturePtr feature, IMessageManager& manager);
    virtual void process_items(IInventoryPtr items, IMessageManager& manager);

    virtual std::string get_item_processed_message(ItemPtr item);
    virtual std::string get_feature_processed_message(FeaturePtr feature);
};

using TileDamageProcessorPtr = std::unique_ptr<TileDamageProcessor>;

