#pragma once
#include "CodexDescriber.hpp"
#include "Wearable.hpp"

class WearableCodexDescriber : public CodexDescriber
{
  public:
    WearableCodexDescriber(WearablePtr wearable);
    WearableCodexDescriber(WearablePtr wearable, const bool desc_protect);

    std::string describe_speed_bonus() const override;
    std::string describe_details() const override;

    void set_always_describe_protect(const bool new_describe_protect);
    bool get_always_describe_protect() const;

  protected:
    bool always_describe_protect;
    WearablePtr wearable;
};

