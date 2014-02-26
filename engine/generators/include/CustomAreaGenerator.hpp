#pragma once
#include "Map.hpp"

// CustomAreaGenerator reads in the custom areas from an XML file on
// disk, generates tiles based on the row data specified in the file, and
// then runs a particular script, if specified.
class CustomAreaGenerator
{
  public:
    CustomAreaGenerator(const std::string& area_filename);
    ~CustomAreaGenerator();

    void overlay_custom_areas(MapPtr map);

  protected:
    std::string filename;
};

