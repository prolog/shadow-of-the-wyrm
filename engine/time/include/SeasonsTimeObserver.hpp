#pragma once
#include "ITimeObserver.hpp"

class SeasonsTimeObserver : public ITimeObserver
{
  public:
    SeasonsTimeObserver();
    
    void notify(const ulonglong minutes_elapsed);

    ITimeObserver* clone();

    // No data members, so just use ITimeObserver's serializer.

  private:
    ClassIdentifier internal_class_identifier() const;
};
