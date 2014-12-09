#pragma once
#include "ITimeObserver.hpp"

class MapTimeObserver : public ITimeObserver
{
  public:
    MapTimeObserver();
    
    void notify(const ulonglong minutes_elapsed) override;

    ITimeObserver* clone() override;

    // No data members, so just use ITimeObserver's serializer.

  private:
    ClassIdentifier internal_class_identifier() const override;
};
