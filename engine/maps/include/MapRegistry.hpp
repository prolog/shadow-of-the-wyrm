#pragma once
#include <map>
#include <string>
#include "ISerializable.hpp"
#include "Map.hpp"
typedef std::map<std::string, MapPtr> MapRegistryMap;

class MapRegistry : public ISerializable
{
  public:
    MapRegistry();
    ~MapRegistry();

    bool set_map(const std::string& map_id, const MapPtr& map);
    MapPtr get_map(const std::string& map_id) const;
    bool remove_map(const std::string& map_id);

    bool serialize(std::ostream& stream) const override;
    bool deserialize(std::istream& stream) override;

  protected:
    MapRegistryMap map_registry;
    
  private:
    ClassIdentifier internal_class_identifier() const override;
};
