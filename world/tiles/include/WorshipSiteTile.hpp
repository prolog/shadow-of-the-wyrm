#pragma once
#include <memory>
#include "WorldMapTile.hpp"
#include "WorshipSiteTypes.hpp"

// The direct parent of church, temple, and sacrifice site tiles.
// Contains additional information specifically required for these
// tiles, such as the deity ID of the deity the site is for.
class WorshipSiteTile : public WorldMapLandmarkTile
{
  public:
    WorshipSiteTile();

    virtual void set_deity_id(const std::string& new_deity_id);
    virtual std::string get_deity_id() const;

    virtual void set_worship_site_type(const WorshipSiteType new_site_type);
    virtual WorshipSiteType get_worship_site_type() const;

    virtual bool serialize(std::ostream& stream) const override;
    virtual bool deserialize(std::istream& stream) override;

  protected:
    std::string deity_id;
    WorshipSiteType site_type;    

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};

using WorshipSiteTilePtr = std::shared_ptr<WorshipSiteTile>;
