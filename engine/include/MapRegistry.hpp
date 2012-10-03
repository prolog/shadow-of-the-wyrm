#pragma once
#include <map>
#include <string>
#include "Map.hpp"

class MapRegistry
{
  public:
    MapRegistry();
    ~MapRegistry();

    bool set_map(const std::string& map_id, const MapPtr& map);
    MapPtr get_map(const std::string& map_id) const;
    bool remove_map(const std::string& map_id);

  protected:
    std::map<std::string, MapPtr> map_registry;
    
  private:
    friend class TemplatesSerialization;
};
