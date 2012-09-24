#pragma once
#include <map>
#include <string>
#include "Map.hpp"

namespace boost
{
  namespace serialization
  {
    class access;
  }
}

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
    friend class boost::serialization::access;
    
    template<typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
      ar & map_registry;
    }
};
