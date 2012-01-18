#pragma once
#include "Item.hpp"

class Staff : public Item
{
  public:
    Staff();
    ~Staff();

  protected:
};

typedef boost::shared_ptr<Staff> StaffPtr;
