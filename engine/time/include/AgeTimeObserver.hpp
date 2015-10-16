#pragma once
#include "ITimeObserver.hpp"

class AgeTimeObserver : public ITimeObserver
{
  public:
    AgeTimeObserver();
    
    void notify(const ulonglong minutes_elapsed) override;

    ITimeObserver* clone() override;

  private:
    ClassIdentifier internal_class_identifier() const override;
};
