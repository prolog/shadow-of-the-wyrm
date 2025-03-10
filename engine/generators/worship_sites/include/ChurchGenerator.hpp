#pragma once
#include <memory>
#include "Generator.hpp"

// Though this class is called "ChurchGenerator", it's actually an
// abstract class for generating churches, templates, and sites of
// threefold death - the names for religious places for good,
// neutral, and evil deities, respectively.
class ChurchGenerator : public SOTW::Generator
{
  public:
    ChurchGenerator(const std::string& new_deity_id, MapPtr new_base_map, const TileType church_type);
    virtual ~ChurchGenerator() = default;

    virtual MapPtr generate() override = 0;
    virtual MapPtr generate(const Dimensions& dim) override = 0;

  protected:
    virtual bool get_permanence_default() const override;
    virtual bool get_ignore_creature_generation_level_checks() const override;

    std::string deity_id;
    MapPtr base_map;
};

using ChurchGeneratorPtr = std::unique_ptr<ChurchGenerator>;
