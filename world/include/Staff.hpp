#pragma once
#include "Item.hpp"

class Staff : public Item
{
  public:
    Staff();
    ~Staff();
};

typedef boost::shared_ptr<Staff> StaffPtr;
