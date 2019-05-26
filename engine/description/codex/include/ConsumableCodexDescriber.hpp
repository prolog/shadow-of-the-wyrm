#include "CodexDescriber.hpp"

class ConsumableCodexDescriber : public CodexDescriber
{
  public: 
    ConsumableCodexDescriber(ItemPtr item);

    std::string describe_for_synopsis_line() const override;
    std::string describe_details() const override;
};

