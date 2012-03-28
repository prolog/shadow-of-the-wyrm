#include "ChurchGenerator.hpp"

// A simple stone church - like the ones that can be seen in the English
// countryside, off the little country roads.
//
// The Lady's followers congregate in such small churches.
class SimpleChurchGenerator : public ChurchGenerator
{
  public:
    SimpleChurchGenerator(const std::string& deity_id, MapPtr base_map);

    virtual MapPtr generate();
    virtual MapPtr generate(const Dimensions& dim);
    
  protected:
    virtual void generate_church(MapPtr map);
};
