#include "CodexDescriber.hpp"

class FoodCodexDescriber : public CodexDescriber
{
  public: 
    FoodCodexDescriber(ItemPtr item);

    std::string describe_for_synopsis_line() const override;
};

