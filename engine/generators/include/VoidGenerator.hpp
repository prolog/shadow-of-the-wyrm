#pragma once
#include "Generator.hpp"

class VoidGenerator : public SOTW::Generator
{
  public:
    VoidGenerator(const std::string& map_exit_id);
    virtual ~VoidGenerator() = default;
    
    virtual MapPtr generate(const Dimensions& dim) override;

  protected:
    virtual MapType get_map_type() const override;

    void add_cosmic_dust(MapPtr result_map);
    void add_celestial_objects(MapPtr result_map);
    void add_spiral_arm(MapPtr result_map);

    void add_random_features(MapPtr result_map, const std::vector<std::string>& feature_ids, const int num_features);

    static const std::string FEATURE_ID_COSMIC_DUST;
    static const std::string FEATURE_ID_DWARF_STAR;
    static const std::string FEATURE_ID_RED_GIANT_STAR;
    static const std::string FEATURE_ID_SUPERNOVA;
    static const std::string FEATURE_ID_BLACK_HOLE;
    static const std::string FEATURE_ID_PULSAR;
    static const std::string FEATURE_ID_SPIRAL_ARM;

    static const int PCT_CHANCE_COSMIC_DUST;
    
    // When there's cosmic dust/features, the rows and cols are multiplied 
    // together (to get the total number of tiles), and then divided by a 
    // divisor to determine how much dust is present.
    static const int COSMIC_DUST_DIV_MIN;
    static const int COSMIC_DUST_DIV_MAX;

    static const int CELESTIAL_OBJECTS_DIV_MIN;
    static const int CELESTIAL_OBJECTS_DIV_MAX;
    
    static const int PCT_CHANCE_CELESTIAL_OBJECTS;

    static const int PCT_CHANCE_SPIRAL_ARM;
    static const int SPIRAL_ARM_DENSITY_PCT_MIN;
    static const int SPIRAL_ARM_DENSITY_PCT_MAX;
};
