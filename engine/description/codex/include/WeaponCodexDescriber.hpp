#include "CodexDescriber.hpp"

class WeaponCodexDescriber : public CodexDescriber
{
  public: 
    WeaponCodexDescriber(ItemPtr item);

    std::string describe_for_synopsis_line() const override;
};

