#include "Religion.hpp"
#include "Deity.hpp"

class ReligionFactory
{
  public:
    static Religion create_religion(const DeityMap& deities);

  protected:
    ReligionFactory();
};
