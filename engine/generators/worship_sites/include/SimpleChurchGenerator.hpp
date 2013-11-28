#include "ChurchGenerator.hpp"

// A simple stone church - like the ones that can be seen in the English
// countryside, off the little country roads.
//
// The Lady's followers congregate in such small churches.
class SimpleChurchGenerator : public ChurchGenerator
{
  public:
    SimpleChurchGenerator(const std::string& deity_id, MapPtr base_map);

    virtual MapPtr generate() override;
    virtual MapPtr generate(const Dimensions& dim) override;
    
  protected:
    virtual void initialize_dimensions(MapPtr map);
    virtual void generate_church(MapPtr map);
    
    virtual void generate_features(MapPtr map);
    virtual void generate_altar(MapPtr map);
    virtual void generate_pews(MapPtr map);
    virtual void generate_door(MapPtr map);
    
    int start_row;
    int start_col;
    int church_height;
    int church_width;
    int altar_row;
};
