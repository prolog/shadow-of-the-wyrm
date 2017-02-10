#pragma once
#include "ITimeObserver.hpp"
#include "Map.hpp"

class ShopsTimeObserver : public ITimeObserver
{
  public:
    ShopsTimeObserver();
    
    void notify(const ulonglong minutes_elapsed) override;

    ITimeObserver* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
