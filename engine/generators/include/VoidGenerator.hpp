#pragma once
#include "Generator.hpp"

class VoidGenerator : public SOTW::Generator
{
  public:
    VoidGenerator(const std::string& map_exit_id);
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    void add_cosmic_dust(MapPtr result_map);
    void add_celestial_objects(MapPtr result_map);
    void add_spiral_arm(MapPtr result_map);

    static const std::string FEATURE_ID_COSMIC_DUST;
    static const std::string FEATURE_ID_DWARF_STAR;
    static const std::string FEATURE_ID_RED_GIANT_STAR;
    static const std::string FEATURE_ID_SUPERNOVA;
    static const std::string FEATURE_ID_BLACK_HOLE;
    static const std::string FEATURE_ID_PULSAR;

    static const int PCT_CHANCE_SPACE_DUST;
    static const int PCT_CHANCE_CELESTIAL_OBJECTS;
    static const int PCT_CHANCE_SPIRAL_ARM;
};
