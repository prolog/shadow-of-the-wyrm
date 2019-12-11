#pragma once
#include "Feature.hpp"

class JewelerWorkbench : public Feature
{
  public:
    JewelerWorkbench(const Symbol& new_symbol);
    virtual Feature* clone() override;

    bool operator==(const JewelerWorkbench& j) const;

  private:
    virtual ClassIdentifier internal_class_identifier() const override;
};
