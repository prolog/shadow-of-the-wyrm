#pragma once
#include <memory>
#include "Generator.hpp"

// Though this class is called "ChurchGenerator", it's actually an
// abstract class for generating churches, templates, and sites of
// threefold death - the names for religious places for lawful,
// neutral, and chaotic deities, respectively.
class ChurchGenerator : public SL::Generator
{
  public:
    ChurchGenerator(const std::string& new_deity_id, MapPtr new_base_map, const TileType church_type);

    virtual MapPtr generate() = 0;
    virtual MapPtr generate(const Dimensions& dim) = 0;

  protected:
    virtual bool get_permanence_default() const;

    std::string deity_id;
    MapPtr base_map;
};

typedef std::shared_ptr<ChurchGenerator> ChurchGeneratorPtr;
