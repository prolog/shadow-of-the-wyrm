#pragma once
#include <boost/shared_ptr.hpp>
#include "Generator.hpp"

// Though this class is called "ChurchGenerator", it's actually an
// abstract class for generating churches, templates, and sites of
// threefold death - the names for religious places for lawful,
// neutral, and chaotic deities, respectively.
class ChurchGenerator : public Generator
{
  public:
    ChurchGenerator(const std::string& new_deity_id, MapPtr new_base_map, const TileType church_type);

    virtual MapPtr generate() = 0;
    virtual MapPtr generate(const Dimensions& dim) = 0;

  protected:
    std::string deity_id;
    MapPtr base_map;
};

typedef boost::shared_ptr<ChurchGenerator> ChurchGeneratorPtr;
